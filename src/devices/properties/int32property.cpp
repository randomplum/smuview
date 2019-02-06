/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018-2019 Frank Stettner <frank-stettner@gmx.net>
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

#include <limits>

#include <QDebug>
#include <QString>
#include <QVariant>

#include "int32property.hpp"
#include "src/devices/configurable.hpp"

namespace sv {
namespace devices {
namespace properties {

Int32Property::Int32Property(shared_ptr<devices::Configurable> configurable,
		devices::ConfigKey config_key) :
	BaseProperty(configurable, config_key),
	min_(std::numeric_limits<int32_t>::lowest()),
	max_(std::numeric_limits<int32_t>::max()),
	step_(1)
{
	if (is_listable_)
		list_config();
}

QVariant Int32Property::value() const
{
	return QVariant(int32_value());
}

int32_t Int32Property::int32_value() const
{
	return configurable_->get_config<int32_t>(config_key_);
}

QString Int32Property::to_string() const
{
	return QString::number(int32_value());
}

int32_t Int32Property::min() const
{
	return min_;
}

int32_t Int32Property::max() const
{
	return max_;
}

int32_t Int32Property::step() const
{
	return step_;
}

bool Int32Property::list_config()
{
	Glib::VariantContainerBase gvar;
	if (!configurable_->list_config(config_key_, gvar))
		return false;

	Glib::VariantIter iter(gvar);
	iter.next_value(gvar);
	min_ = Glib::VariantBase::cast_dynamic<Glib::Variant<int32_t>>(gvar).get();
	iter.next_value(gvar);
	max_ = Glib::VariantBase::cast_dynamic<Glib::Variant<int32_t>>(gvar).get();
	iter.next_value(gvar);
	step_ = Glib::VariantBase::cast_dynamic<Glib::Variant<int32_t>>(gvar).get();

	return true;
}

void Int32Property::change_value(const QVariant qvar)
{
	configurable_->set_config(config_key_, qvar.toInt());
	Q_EMIT value_changed(qvar);
}

void Int32Property::on_value_changed(Glib::VariantBase g_var)
{
	Q_EMIT value_changed(QVariant(g_variant_get_int32(g_var.gobj())));
}

} // namespace datatypes
} // namespace devices
} // namespace sv
