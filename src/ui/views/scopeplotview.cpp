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

#include <cassert>
#include <string>

#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QToolButton>
#include <QVBoxLayout>

#include "scopeplotview.hpp"
#include "src/session.hpp"
#include "src/settingsmanager.hpp"
#include "src/util.hpp"
#include "src/channels/basechannel.hpp"
#include "src/data/analogtimesignal.hpp"
#include "src/devices/basedevice.hpp"
#include "src/ui/dialogs/selectsignaldialog.hpp"
#include "src/ui/views/baseplotview.hpp"
#include "src/ui/views/viewhelper.hpp"
#include <src/ui/widgets/plot/curve.hpp>
#include "src/ui/widgets/plot/plot.hpp"
#include "src/ui/widgets/plot/basecurvedata.hpp"

using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::string;
using sv::devices::ConfigKey;

Q_DECLARE_METATYPE(sv::ui::widgets::plot::BaseCurveData *)

namespace sv {
namespace ui {
namespace views {

ScopePlotView::ScopePlotView(Session &session, QUuid uuid, QWidget *parent) :
	BasePlotView(session, uuid, parent)
{
	id_ = "scopeplot:" + util::format_uuid(uuid_);
	plot_type_ = PlotType::ScopePlot;
}

QString ScopePlotView::title() const
{
	QString title = tr("Channel").append(" MÖÖÖP"); //.append(channel_->display_name()); TODO
	return title;
}

string ScopePlotView::add_channel(shared_ptr<channels::BaseChannel> channel)
{
	(void)channel;
	/*
	if (!plot_->add_channel(channel->display_name()))
		return;

	// TODO
	channel_2_ = channel;
	shared_ptr<data::AnalogTimeSignal> signal;
	if (channel_2_->actual_signal())
		signal = static_pointer_cast<data::AnalogTimeSignal>(
			channel_2_->actual_signal());
	if (signal)
		plot_->show_curve(channel->display_name(),
			new widgets::plot::TimeCurveData(signal));

	connect(channel_2_.get(),
		SIGNAL(signal_added(shared_ptr<sv::data::BaseSignal>)),
		this, SLOT(on_signal_added()));
	*/


	/*
		update_add_marker_menu();
	}
	else {
		QMessageBox::warning(this,
			tr("Cannot add signal"), tr("Cannot add time signal to plot!"),
			QMessageBox::Ok);
	}
	*/

	return "";
}

void ScopePlotView::save_settings(QSettings &settings,
	shared_ptr<sv::devices::BaseDevice> origin_device) const
{
	BasePlotView::save_settings(settings, origin_device);

	/*
	// TODO: Can the channel be saved inside the plot widget?
	bool save_curves = true;
	if (channel_) {
		SettingsManager::save_channel(channel_, settings, origin_device);
		save_curves = false;
	}
	plot_->save_settings(settings, save_curves, origin_device);
	*/
}

void ScopePlotView::restore_settings(QSettings &settings,
	shared_ptr<sv::devices::BaseDevice> origin_device)
{
	BasePlotView::restore_settings(settings, origin_device);

	/*
	// TODO: Can the channel be restored inside the plot widget?
	bool restore_curves = true;
	auto channel = SettingsManager::restore_channel(
		session_, settings, origin_device);
	if (channel) {
		set_channel(channel);
		restore_curves = false;
	}
	plot_->restore_settings(settings, restore_curves, origin_device);
	*/
}

} // namespace views
} // namespace ui
} // namespace sv
