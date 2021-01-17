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

#ifndef UI_VIEWS_SCOPEPLOTVIEW_HPP
#define UI_VIEWS_SCOPEPLOTVIEW_HPP

#include <memory>
#include <string>

#include <QSettings>
#include <QUuid>

#include "src/ui/views/baseplotview.hpp"

using std::shared_ptr;
using std::string;

namespace sv {

class Session;

namespace channels {
class BaseChannel;
}
namespace data {
class AnalogTimeSignal;
}
namespace devices {
class OscilloscopeDevice;
}

namespace ui {
namespace views {

class ScopePlotView : public BasePlotView
{
	Q_OBJECT

public:
	explicit ScopePlotView(Session &session, QUuid uuid = QUuid(),
		QWidget *parent = nullptr);
	/*
	ScopePlotView(Session &session,
		shared_ptr<sv::devices::OscilloscopeDevice> device,
		shared_ptr<channels::BaseChannel> x_channel,
		shared_ptr<channels::BaseChannel> y_channel,
		QWidget *parent = nullptr);
	*/

	QString title() const override;

	void save_settings(QSettings &settings,
		shared_ptr<sv::devices::BaseDevice> origin_device = nullptr) const override;
	void restore_settings(QSettings &settings,
		shared_ptr<sv::devices::BaseDevice> origin_device = nullptr) override;

	/**
	 * Add a new channel to the scope plot and return the curve id.
	 */
	string add_channel(shared_ptr<channels::BaseChannel> channel);

private:
	vector<shared_ptr<channels::BaseChannel>> channels_;

protected Q_SLOTS:
	void on_action_add_curve_triggered() override;

};

} // namespace views
} // namespace ui
} // namespace sv

#endif // UI_VIEWS_SCOPEPLOTVIEW_HPP
