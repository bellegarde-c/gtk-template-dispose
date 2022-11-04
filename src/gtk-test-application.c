/* gtk-test-application.c
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

#include "gtk-test-application.h"
#include "gtk-test-window.h"

struct _GtkTestApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_TYPE (GtkTestApplication, gtk_test_application, ADW_TYPE_APPLICATION)

GtkTestApplication *
gtk_test_application_new (const char        *application_id,
                          GApplicationFlags  flags)
{
  g_return_val_if_fail (application_id != NULL, NULL);

  return g_object_new (GTK_TEST_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
gtk_test_application_activate (GApplication *app)
{
  GtkWindow *window;

  g_assert (GTK_TEST_IS_APPLICATION (app));

  window = gtk_application_get_active_window (GTK_APPLICATION (app));
  if (window == NULL)
    window = g_object_new (GTK_TEST_TYPE_WINDOW,
                           "application", app,
                           NULL);

  gtk_window_present (window);
  gtk_window_add_label (GTK_TEST_WINDOW(window));
  gtk_window_add_label (GTK_TEST_WINDOW(window));
  gtk_window_add_label (GTK_TEST_WINDOW(window));
}

static void
gtk_test_application_class_init (GtkTestApplicationClass *klass)
{
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  app_class->activate = gtk_test_application_activate;
}

static void
gtk_test_application_about_action (GSimpleAction *action,
                                   GVariant      *parameter,
                                   gpointer       user_data)
{
  static const char *developers[] = {"Cédric Bellegarde", NULL};
  GtkTestApplication *self = user_data;
  GtkWindow *window = NULL;

  g_assert (GTK_TEST_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  adw_show_about_window (window,
                         "application-name", "gtk-test",
                         "application-icon", "org.gnome.gtk_test",
                         "developer-name", "Cédric Bellegarde",
                         "version", "0.1.0",
                         "developers", developers,
                         "copyright", "© 2022 Cédric Bellegarde",
                         NULL);
}

static void
gtk_test_application_quit_action (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
  GtkTestApplication *self = user_data;

  g_assert (GTK_TEST_IS_APPLICATION (self));

  g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
  { "quit", gtk_test_application_quit_action },
  { "about", gtk_test_application_about_action },
};

static void
gtk_test_application_init (GtkTestApplication *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   app_actions,
                                   G_N_ELEMENTS (app_actions),
                                   self);
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "app.quit",
                                         (const char *[]) { "<primary>q", NULL });
}


