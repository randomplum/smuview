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

#ifndef UI_WIDGETS_PLOT_SCOPECURVEDATA_HPP
#define UI_WIDGETS_PLOT_SCOPECURVEDATA_HPP

#include <memory>

#include <QPointF>
#include <QRectF>
#include <QString>

#include "src/ui/widgets/plot/basecurvedata.hpp"

using std::shared_ptr;

namespace sv {

namespace data {
class AnalogScopeSignal;
}

namespace ui {
namespace widgets {
namespace plot {

class ScopeCurveData : public BaseCurveData
{

public:
	ScopeCurveData(shared_ptr<sv::data::AnalogScopeSignal> signal);

	QString name() const override;
	string id_prefix() const override;

	bool is_equal(const BaseCurveData *other) const override;

	QPointF sample(size_t i) const override;
	size_t size() const override;
	QRectF boundingRect() const override;

	QPointF closest_point(const QPointF &pos, double *dist) const override;
	sv::data::Quantity x_quantity() const override;
	set<sv::data::QuantityFlag> x_quantity_flags() const override;
	sv::data::Unit x_unit() const override;
	QString x_unit_str() const override;
	QString x_title() const override;
	sv::data::Quantity y_quantity() const override;
	set<sv::data::QuantityFlag> y_quantity_flags() const override;
	sv::data::Unit y_unit() const override;
	QString y_unit_str() const override;
	QString y_title() const override;

	void save_settings(QSettings &settings,
		shared_ptr<sv::devices::BaseDevice> origin_device) const override;

	shared_ptr<sv::data::AnalogScopeSignal> signal() const;

private:
	shared_ptr<sv::data::AnalogScopeSignal> signal_;

};

} // namespace plot
} // namespace widgets
} // namespace ui
} // namespace sv

#endif // UI_WIDGETS_PLOT_SCOPECURVEDATA_HPP
