#include <stdio.h>
#include <string.h>
#include <miner.h>
#undef max
#undef min
#include "core/Config.h"
#include "core/Controller.h"
#include "interfaces/IThread.h"

struct cryptonight_ctx {
    alignas(16) uint8_t state[224];
    alignas(16) uint8_t *memory;
};

extern "C" int scanhash_cryptonight_keva(int thr_id, void* threadInfo, struct work* work, uint32_t max_nonce, unsigned long *hashes_done, int _variant)
{
	int res = 0;
	uint32_t *ptarget = work->target;
	const uint32_t Htarg = ptarget[7];
	uint64_t* target64 = (uint64_t*)(&ptarget[6]); // endanese?
	uint8_t *pdata = (uint8_t*) work->data;
	uint32_t *nonceptr = (uint32_t*) (&work->data[19]);
	const uint32_t first_nonce = *nonceptr;
	const xmrig::Algo algorithm  = xmrig::CRYPTONIGHT;
	const xmrig::Variant variant = xmrig::VARIANT_2;
	if(opt_benchmark) {
		ptarget[7] = 0x00ff;
	}

	do
	{
		cryptonight_ctx* ctx;
		uint32_t hash[8];
		xmrig::CpuThread* thread = reinterpret_cast<xmrig::CpuThread*>(threadInfo);
		thread->fn(variant)(pdata, 80, (uint8_t*)hash, &ctx);
		*hashes_done ++;
		if(hash[7] <= Htarg && fulltest(hash, ptarget)) {
			work->nonces[0] = *nonceptr;
			work_set_target_ratio(work, hash);
			res = 1;
			goto done;
		}
		*nonceptr ++;
	} while (!work_restart[thr_id].restart && max_nonce > *nonceptr);

done:
	gpulog(LOG_DEBUG, thr_id, "nonce %08x exit", *nonceptr);
	work->valid_nonces = res;
	if (res == 1) {
		*nonceptr = work->nonces[0];
	}
	return res;
}

#if 0
extern "C" int scanhash_cryptonight_keva(int thr_id, struct work* work, uint32_t max_nonce, unsigned long *hashes_done, int _variant)
{
	int res = 0;
	uint32_t *ptarget = work->target;
	const uint32_t Htarg = ptarget[7];
	uint64_t* target64 = (uint64_t*)(&ptarget[6]); // endanese?
	uint8_t *pdata = (uint8_t*) work->data;
	uint32_t *nonceptr = (uint32_t*) (&work->data[19]);
	const uint32_t first_nonce = *nonceptr;
	const xmrig::Algo algorithm  = xmrig::CRYPTONIGHT;
	const xmrig::Variant variant = xmrig::VARIANT_2;
	if(opt_benchmark) {
		ptarget[7] = 0x00ff;
	}

	contexts[thr_id].Nonce = first_nonce;

	do
	{
		uint32_t foundCount = 0;
		cl_uint results[0x100];
		XMRSetJob(&contexts[thr_id], (uint8_t*)(work->data), 80, *target64, xmrig::VARIANT_2);
		memset(results, 0, sizeof(results));

		XMRRunJob(&contexts[thr_id], results, xmrig::VARIANT_2);
		//*hashes_done = contexts[thr_id].Nonce;
		*hashes_done = contexts[thr_id].Nonce - first_nonce;
		res = 0;
		foundCount = results[0xff];
		for (size_t i = 0; i < foundCount; i++) {
			uint32_t vhash[8];
			uint32_t tempdata[20];
			uint32_t *tempnonceptr = (uint32_t*)(&tempdata[19]);
			memcpy(tempdata, pdata, 80);
			*tempnonceptr = results[i];
			cryptonight_hash((const char*)tempdata, (char*)vhash, 80, variant);
			if(vhash[7] <= Htarg && fulltest(vhash, ptarget)) {
				work->nonces[i] = results[i];
				work_set_target_ratio(work, vhash);
				res ++;
			} else if (!opt_quiet) {
				gpulog(LOG_WARNING, thr_id, "result for nonce %08x does not validate on CPU!", results[i]);
			}
		}
		if (res > 0) {
			goto done;
		}
	} while (!work_restart[thr_id].restart && max_nonce > contexts[thr_id].Nonce);

done:
	gpulog(LOG_DEBUG, thr_id, "nonce %08x exit", contexts[thr_id].Nonce);
	work->valid_nonces = res;
	if (res == 1) {
		*nonceptr = work->nonces[0];
	} else if (res == 2) {
		*nonceptr = (work->nonces[0] > work->nonces[1]) ? work->nonces[0] : work->nonces[1];
	} else {
		*nonceptr = contexts[thr_id].Nonce;
	}
	return res;
}
#endif