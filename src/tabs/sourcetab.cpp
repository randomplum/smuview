/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
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

#include <QHBoxLayout>
#include <QGroupBox>

#include "sourcetab.hpp"
#include "src/tabs/devicetab.hpp"
#include "src/data/analogdata.hpp"
#include "src/data/basesignal.hpp"
#include "src/views/sourcecontrolview.hpp"
#include "src/views/plotview.hpp"
#include "src/views/powerpanelview.hpp"

namespace sv {
namespace tabs {

SourceTab::SourceTab(Session &session,
		shared_ptr<devices::HardwareDevice> device, QMainWindow *parent) :
	DeviceTab(session, device, parent)
{
	setup_ui();
}

void SourceTab::setup_ui()
{
	// Device controls
	if (device_->is_controllable()) {
		shared_ptr<views::BaseView> control_view =
			make_shared<views::SourceControlView>(session_, device_);
		add_view(tr("Device control"), control_view,
			Qt::TopDockWidgetArea, session_);
	}

	// Power panel
	if (device_->voltage_signal() && device_->current_signal()) {
		shared_ptr<views::BaseView> power_panel_view =
			make_shared<views::PowerPanelView>(session_,
				device_->voltage_signal(), device_->current_signal());
		add_view(tr("Power Panel"), power_panel_view,
			Qt::TopDockWidgetArea, session_);
	}

	// Voltage plot
	if (device_->voltage_signal()) {
		shared_ptr<views::BaseView> voltage_plot_view =
			make_shared<views::PlotView>(session_,
				device_->voltage_signal()->time_data(),
				device_->voltage_signal()->analog_data());
		add_view(tr("Voltage Graph"), voltage_plot_view,
			Qt::BottomDockWidgetArea, session_);
	}

	// Current plot
	if (device_->current_signal()) {
		shared_ptr<views::BaseView> current_plot_view =
			make_shared<views::PlotView>(session_,
				device_->current_signal()->time_data(),
				device_->current_signal()->analog_data());
		add_view(tr("Current Graph"), current_plot_view,
			Qt::BottomDockWidgetArea, session_);
	}

	// UI plot
	if (device_->current_signal()) {
		shared_ptr<views::BaseView> ui_plot_view =
			make_shared<views::PlotView>(session_,
				device_->voltage_signal()->analog_data(),
				device_->current_signal()->analog_data());
		add_view(tr("UI Graph"), ui_plot_view,
			Qt::BottomDockWidgetArea, session_);
	}
}

} // namespace tabs
} // namespace sv
