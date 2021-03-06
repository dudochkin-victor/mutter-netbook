
/*
 * Copyright (c) 2010 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Author: Rob Staudinger <robsta@linux.intel.com>
 */

#ifndef MPL_APP_LAUNCHES_STORE_H
#define MPL_APP_LAUNCHES_STORE_H

#include <stdbool.h>
#include <stdint.h>
#include <glib-object.h>
#include <meego-panel/mpl-app-launches-query.h>

G_BEGIN_DECLS

#define MPL_TYPE_APP_LAUNCHES_STORE mpl_app_launches_store_get_type()

#define MPL_APP_LAUNCHES_STORE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), MPL_TYPE_APP_LAUNCHES_STORE, MplAppLaunchesStore))

#define MPL_APP_LAUNCHES_STORE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), MPL_TYPE_APP_LAUNCHES_STORE, MplAppLaunchesStoreClass))

#define MPL_IS_APP_LAUNCHES_STORE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MPL_TYPE_APP_LAUNCHES_STORE))

#define MPL_IS_APP_LAUNCHES_STORE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), MPL_TYPE_APP_LAUNCHES_STORE))

#define MPL_APP_LAUNCHES_STORE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), MPL_TYPE_APP_LAUNCHES_STORE, MplAppLaunchesStoreClass))

typedef struct
{
  GObject parent;
} MplAppLaunchesStore;

typedef struct
{
  GObjectClass parent;
} MplAppLaunchesStoreClass;

enum
{
  MPL_APP_LAUNCHES_STORE_ERROR_OPENING_DATABASE,
  MPL_APP_LAUNCHES_STORE_ERROR_READING_DATABASE,
  MPL_APP_LAUNCHES_STORE_ERROR_WRITING_DATABASE,
  MPL_APP_LAUNCHES_STORE_ERROR_CLOSING_DATABASE
};

GType
mpl_app_launches_store_get_type (void);

MplAppLaunchesStore *
mpl_app_launches_store_new (void);

bool
mpl_app_launches_store_add (MplAppLaunchesStore  *self,
                            char const           *executable,
                            time_t                timestamp,
                            GError              **error);

bool
mpl_app_launches_store_add_async (MplAppLaunchesStore  *self,
                                  char const           *executable,
                                  time_t                timestamp,
                                  GError              **error);

bool
mpl_app_launches_store_lookup (MplAppLaunchesStore   *self,
                               char const            *executable,
                               time_t                *last_launched_out,
                               uint32_t              *n_launches_out,
                               GError               **error);

bool
mpl_app_launches_store_dump (MplAppLaunchesStore   *self,
                             GError               **error);

MplAppLaunchesQuery *
mpl_app_launches_store_create_query (MplAppLaunchesStore *self);

G_END_DECLS

#endif /* MPL_APP_LAUNCHES_STORE_H */

