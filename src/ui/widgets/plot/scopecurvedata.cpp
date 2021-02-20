/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2019-2021 Frank Stettner <frank-stettner@gmx.net>
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

#include <memory>

#include <QPointF>
#include <QRectF>
#include <QString>

#include "scopecurvedata.hpp"
#include "src/data/analogscopesignal.hpp"
#include "src/data/datautil.hpp"
#include "src/ui/widgets/plot/basecurvedata.hpp"

using std::shared_ptr;

namespace sv {
namespace ui {
namespace widgets {
namespace plot {

ScopeCurveData::ScopeCurveData(shared_ptr<sv::data::AnalogScopeSignal> signal) :
	BaseCurveData(CurveType::ScopeCurve),
	signal_(signal)
{
}

bool ScopeCurveData::is_equal(const BaseCurveData *other) const
{
	const ScopeCurveData *scd = dynamic_cast<const ScopeCurveData *>(other);
	if (scd == nullptr)
		return false;

	return signal_ == scd->signal();
}

QPointF ScopeCurveData::sample(size_t i) const
{
	//signal_data_->lock();

	auto sample = signal_->get_sample(i);
	QPointF sample_point(sample.first, sample.second);

	//signal_data_->.unlock();

	return sample_point;
}

size_t ScopeCurveData::size() const
{
	// TODO: Synchronize x/y sample data
	return signal_->sample_count();
}

QRectF ScopeCurveData::boundingRect() const
{
	qWarning() << "ScopeCurveData::boundingRect(): min time = "
		<< signal_->first_timestamp();
	qWarning() << "ScopeCurveData::boundingRect(): max time = "
		<< signal_->last_timestamp();
	qWarning() << "ScopeCurveData::boundingRect(): min value = "
		<< signal_->min_value();
	qWarning() << "ScopeCurveData::boundingRect(): max value = "
		<< signal_->max_value();

	// top left, bottom right
	return QRectF(
		QPointF(signal_->first_timestamp(), signal_->max_value()),
		QPointF(signal_->last_timestamp(), signal_->min_value()));
}

QPointF ScopeCurveData::closest_point(const QPointF &pos, double *dist) const
{
	(void)dist;
	const double x_value = pos.x();
	const int index_max = size() - 1;

	if (index_max < 0 || x_value >= sample(index_max).x())
		return QPointF(0, 0); // TODO

	size_t index_min = 0;
	size_t n = index_max;

	while (n > 0) {
		const size_t half = n >> 1;
		const size_t index_mid = index_min + half;

		if (x_value < sample(index_mid).x()) {
			n = half;
		}
		else {
			index_min = index_mid + 1;
			n -= half + 1;
		}
	}

	return sample(index_min);
}

QString ScopeCurveData::name() const
{
	return signal_->display_name();
}

string ScopeCurveData::id_prefix() const
{
	return "scopecurve";
}

sv::data::Quantity ScopeCurveData::x_quantity() const
{
	return sv::data::Quantity::Time;
}

set<sv::data::QuantityFlag> ScopeCurveData::x_quantity_flags() const
{
	return set<data::QuantityFlag>();
}

sv::data::Unit ScopeCurveData::x_unit() const
{
	return sv::data::Unit::Second;
}

QString ScopeCurveData::x_unit_str() const
{
	return data::datautil::format_unit(x_unit());
}

QString ScopeCurveData::x_title() const
{
	return QString("%1 [%2]").
		arg(data::datautil::format_quantity(x_quantity()), x_unit_str());
}

sv::data::Quantity ScopeCurveData::y_quantity() const
{
	return signal_->quantity();
}

set<sv::data::QuantityFlag> ScopeCurveData::y_quantity_flags() const
{
	return signal_->quantity_flags();
}

sv::data::Unit ScopeCurveData::y_unit() const
{
	return signal_->unit();
}

QString ScopeCurveData::y_unit_str() const
{
	return data::datautil::format_unit(y_unit(), y_quantity_flags());
}

QString ScopeCurveData::y_title() const
{
	// Don't use only the unit, so we can add AC/DC to axis label.
	return QString("%1 [%2]").
		arg(data::datautil::format_quantity(y_quantity()), y_unit_str());
}

void ScopeCurveData::save_settings(QSettings &settings,
	shared_ptr<sv::devices::BaseDevice> origin_device) const
{
	(void)settings;
	(void)origin_device;
}

shared_ptr<sv::data::AnalogScopeSignal> ScopeCurveData::signal() const
{
	return signal_;
}

} // namespace plot
} // namespace widgets
} // namespace ui
} // namespace sv
