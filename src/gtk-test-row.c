/* gtk-test-row.c
 *
 * Copyright 2022 Cédric Bellegarde
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
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "gtk-test-row.h"

struct _GtkTestRow
{
  GtkListBoxRow  parent_instance;
};

G_DEFINE_FINAL_TYPE (GtkTestRow, gtk_test_row, GTK_TYPE_LIST_BOX_ROW)


static void gtk_test_row_dispose (GObject *obj) {
  GtkWidget *widget = GTK_WIDGET (obj);
  gtk_widget_dispose_template (widget, GTK_TYPE_LIST_BOX_ROW);
  G_OBJECT_CLASS (gtk_test_row_parent_class)->dispose (obj);
}

static void
gtk_test_row_class_init (GtkTestRowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/gtk_test/gtk-test-row.ui");
  G_OBJECT_CLASS (klass)->dispose = gtk_test_row_dispose;
}

static void
gtk_test_row_init (GtkTestRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
