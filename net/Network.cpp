/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2016-2018 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif

#include <inttypes.h>
#include <memory>
#include <time.h>


#include "api/Api.h"
#include "common/log/Log.h"
#include "common/net/Client.h"
#include "common/net/strategies/FailoverStrategy.h"
#include "common/net/strategies/SinglePoolStrategy.h"
#include "common/net/SubmitResult.h"
#include "core/Config.h"
#include "core/Controller.h"
#include "net/Network.h"
#include "workers/Workers.h"


Network::Network(xmrig::Controller *controller) :
    m_controller(controller)
{
    srand(time(0) ^ (uintptr_t) this);

    Workers::setListener(this);

    const std::vector<Pool> &pools = controller->config()->pools();
    m_timer.data = this;
    uv_timer_init(uv_default_loop(), &m_timer);

    uv_timer_start(&m_timer, Network::onTick, kTickInterval, kTickInterval);
}


Network::~Network()
{
}


void Network::connect()
{
}


void Network::stop()
{
}


void Network::onActive(IStrategy *strategy, Client *client)
{
}


void Network::onJob(IStrategy *strategy, Client *client, const Job &job)
{
}


void Network::onJobResult(const JobResult &result)
{
}


void Network::onPause(IStrategy *strategy)
{
}


void Network::onResultAccepted(IStrategy *strategy, Client *client, const SubmitResult &result, const char *error)
{
}


bool Network::isColors() const
{
	return false;
}


void Network::setJob(Client *client, const Job &job, bool donate)
{
}


void Network::tick()
{
}


void Network::onTick(uv_timer_t *handle)
{
}
