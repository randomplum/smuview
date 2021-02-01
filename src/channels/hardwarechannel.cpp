/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017-2021 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <memory>
#include <set>
#include <string>
#include <utility>

#include <QDebug>

#include <libsigrokcxx/libsigrokcxx.hpp>

#include "hardwarechannel.hpp"
#include "src/session.hpp"
#include "src/util.hpp"
#include "src/channels/basechannel.hpp"
#include "src/data/analogtimesignal.hpp"
#include "src/data/datautil.hpp"
#include "src/devices/basedevice.hpp"

using std::make_pair;
using std::set;
using std::static_pointer_cast;
using std::string;
using std::unique_ptr;
using sv::data::measured_quantity_t;

namespace sv {
namespace channels {

HardwareChannel::HardwareChannel(
		shared_ptr<sigrok::Channel> sr_channel,
		shared_ptr<devices::BaseDevice> parent_device,
		const set<string> &channel_group_names,
		double channel_start_timestamp) :
	BaseChannel(sr_channel, parent_device, channel_group_names,
		channel_start_timestamp)
{
	assert(sr_channel);

	name_ = sr_channel_->name();
}

} // namespace channels
} // namespace sv
