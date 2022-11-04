/* gtk-test-window.c
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

#include "gtk-test-window.h"
#include "gtk-test-row.h"

struct _GtkTestWindow
{
  AdwApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkListBox            *listbox;
  GtkWidget             *previous;
};

G_DEFINE_FINAL_TYPE (GtkTestWindow, gtk_test_window, ADW_TYPE_APPLICATION_WINDOW)

static void
gtk_test_window_class_init (GtkTestWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/gtk_test/gtk-test-window.ui");
  gtk_widget_class_bind_template_child (widget_class, GtkTestWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, GtkTestWindow, listbox);
}

static void
gtk_test_window_init (GtkTestWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

struct Data {
  GtkListBox *listbox;
  GtkWidget *row;
};


static int
remove_row(gpointer p) {
  struct Data *data = p;
  gtk_list_box_remove(data->listbox, data->row);
  return 0;
}

void
gtk_window_add_label (GtkTestWindow *self) {
  GtkWidget *row = g_object_new (GTK_TEST_TYPE_ROW, NULL);

  if (self->previous != NULL) {
    struct Data *data = malloc(sizeof(struct Data));
    data->listbox = self->listbox;
    data->row = self->previous;
    //g_timeout_add_seconds(5, remove_row, (gpointer) data);
    remove_row((gpointer) data);
    self->previous = NULL;
  }

  self->previous = row;
  gtk_list_box_append(self->listbox, row);
}

