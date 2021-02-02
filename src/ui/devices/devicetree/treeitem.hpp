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

#ifndef UI_DEVICES_DEVICETREE_TREEITEM_HPP
#define UI_DEVICES_DEVICETREE_TREEITEM_HPP

#include <QStandardItem>
#include <QIcon>

namespace sv {
namespace ui {
namespace devices {
namespace devicetree {

enum class TreeItemType {
	DeviceItem = 1001,
	ChannelGroupItem = 1002,
	ChannelItem = 1003,
	ScopeChannelItem = 1004,
	SignalItem = 1005,
	ScopeSignalItem = 1006,
	ConfigurableItem = 1007,
	PropertyItem = 1008,
};

class TreeItem : public QStandardItem
{

public:
	explicit TreeItem(TreeItemType type);

	int type() const override;

protected:
	const TreeItemType type_;

};

} // namespace devicetree
} // namespace devices
} // namespace ui
} // namespace sv

#endif // UI_DEVICES_DEVICETREE_TREEITEM_HPP
