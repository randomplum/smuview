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
#include <vector>

#include <QSettings>
#include <QUuid>

#include "src/ui/views/baseview.hpp"

using std::shared_ptr;
using std::string;
using std::vector;

namespace sv {

class Session;

namespace channels {
class ScopeChannel;
}
namespace data {
class AnalogTimeSignal;
}
namespace devices {
class OscilloscopeDevice;
}

namespace ui {

namespace widgets {
namespace plot {
class  ScopeCurveData;
class  ScopePlot;
}
}

namespace views {

/* TODO
enum class PlotType {
	TimePlot,
	XYPlot,
};
*/

class ScopePlotView : public BaseView
{
	Q_OBJECT

public:
	explicit ScopePlotView(Session &session, QUuid uuid = QUuid(),
		QWidget *parent = nullptr);

	QString title() const override;

	void set_device(shared_ptr<sv::devices::OscilloscopeDevice> device);
	/**
	 * Add a new scope channel to the scope plot and return the curve id.
	 */
	string add_channel(shared_ptr<channels::ScopeChannel> channel);

	void save_settings(QSettings &settings,
		shared_ptr<sv::devices::BaseDevice> origin_device = nullptr) const override;
	void restore_settings(QSettings &settings,
		shared_ptr<sv::devices::BaseDevice> origin_device = nullptr) override;

private:
	void setup_ui();
	void setup_toolbar();
	void update_add_marker_menu();
	void connect_signals();

	shared_ptr<channels::ScopeChannel> channel_1_;
	shared_ptr<channels::ScopeChannel> channel_2_;
	vector<shared_ptr<channels::ScopeChannel>> channels_;
	vector<widgets::plot::ScopeCurveData *> curves_;

	/*
	QMenu *add_marker_menu_;
	QToolButton *add_marker_button_;
	QAction *const action_add_marker_;
	QAction *const action_add_diff_marker_;
	QAction *const action_zoom_best_fit_;
	QAction *const action_add_signal_;
	QAction *const action_config_plot_;
	*/
	QToolBar *toolbar_;
	widgets::plot::ScopePlot *plot_;

protected Q_SLOTS:
	void on_signal_added();
	/*
	void on_action_add_marker_triggered();
	void on_action_add_diff_marker_triggered();
	void on_action_zoom_best_fit_triggered();
	void on_action_add_signal_triggered();
	void on_action_config_plot_triggered();
	*/
	//void on_action_add_curve_triggered();

};

} // namespace views
} // namespace ui
} // namespace sv

#endif // UI_VIEWS_SCOPEPLOTVIEW_HPP
