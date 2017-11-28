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

#ifndef WIDGETS_OPTIONALVALUECONTROL_HPP
#define WIDGETS_OPTIONALVALUECONTROL_HPP

#include <memory>

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QString>
#include <QWidget>

using std::shared_ptr;

namespace sv {

namespace devices {
class HardwareDevice;
}

namespace widgets {

class ControlButton;

class OptionalValueControl : public QGroupBox
{
    Q_OBJECT

public:
	OptionalValueControl(
		bool (devices::HardwareDevice::*get_state_caller)() const,
		void (devices::HardwareDevice::*set_state_caller)(const bool),
		bool (devices::HardwareDevice::*is_state_getable_caller)() const,
		bool (devices::HardwareDevice::*is_state_setable_caller)() const,
		double (devices::HardwareDevice::*get_value_caller)() const,
		void (devices::HardwareDevice::*set_value_caller)(const double),
		bool (devices::HardwareDevice::*is_value_getable_caller)() const,
		bool (devices::HardwareDevice::*is_value_setable_caller)() const,
		shared_ptr<devices::HardwareDevice> device,
		const QString title, const QString unit,
		const double min, const double max, const double steps,
		QWidget *parent = 0);

private:
	bool (devices::HardwareDevice::*get_state_caller_)() const;
	void (devices::HardwareDevice::*set_state_caller_)(const bool);
	bool (devices::HardwareDevice::*is_state_getable_caller_)() const;
	bool (devices::HardwareDevice::*is_state_setable_caller_)() const;
	double (devices::HardwareDevice::*get_value_caller_)() const;
	void (devices::HardwareDevice::*set_value_caller_)(const double);
	bool (devices::HardwareDevice::*is_value_getable_caller_)() const;
	bool (devices::HardwareDevice::*is_value_setable_caller_)() const;
	shared_ptr<devices::HardwareDevice> device_;

	QString title_;
	bool state_;
	double value_;
	QString unit_;
	double min_;
	double max_;
	double steps_;

	bool is_state_enabled_;
	bool is_state_getable_;
	bool is_state_setable_;
	bool is_value_getable_;
	bool is_value_setable_;

	widgets::ControlButton *controlButton;
	QDoubleSpinBox *doubleSpinBox;

	void setup_ui();
	void connect_signals();

public Q_SLOTS:
	void on_clicked();
	void change_state(const bool state);
	void on_state_changed(const bool state);
	void change_value(const double value);
	void on_value_changed(const double value);

Q_SIGNALS:
	void state_changed(const bool state);
	void value_changed(const double value);

};

} // namespace widgets
} // namespace sv

#endif // WIDGETS_OPTIONALVALUECONTROL_HPP
