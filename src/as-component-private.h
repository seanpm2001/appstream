/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2012-2022 Matthias Klumpp <matthias@tenstral.net>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the license, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __AS_COMPONENT_PRIVATE_H
#define __AS_COMPONENT_PRIVATE_H

#include "as-component.h"
#include "as-macros-private.h"
#include "as-tag.h"
#include "as-xml.h"
#include "as-yaml.h"

AS_BEGIN_PRIVATE_DECLS

/**
 * AsOriginKind:
 * @AS_ORIGIN_KIND_UNKNOWN:		Unknown origin kind.
 * @AS_ORIGIN_KIND_METAINFO:		Origin was a metainfo file.
 * @AS_ORIGIN_KIND_CATALOG:		Origin was an AppStream catalog file.
 * @AS_ORIGIN_KIND_DESKTOP_ENTRY:	Origin was a .desktop file.
 *
 * Scope of the #AsComponent (system-wide or user-scope)
 **/
typedef enum {
	AS_ORIGIN_KIND_UNKNOWN,
	AS_ORIGIN_KIND_METAINFO,
	AS_ORIGIN_KIND_CATALOG,
	AS_ORIGIN_KIND_DESKTOP_ENTRY,
	/*< private >*/
	AS_ORIGIN_KIND_LAST
} AsOriginKind;

/**
 * AsSearchTokenMatch:
 * @AS_SEARCH_TOKEN_MATCH_NONE:			No token matching
 * @AS_SEARCH_TOKEN_MATCH_MEDIATYPE:		Use the component mediatypes
 * @AS_SEARCH_TOKEN_MATCH_PKGNAME:		Use the component package name
 * @AS_SEARCH_TOKEN_MATCH_ORIGIN:		Use the app origin
 * @AS_SEARCH_TOKEN_MATCH_DESCRIPTION:		Use the component description
 * @AS_SEARCH_TOKEN_MATCH_COMMENT:		Use the component comment
 * @AS_SEARCH_TOKEN_MATCH_NAME:			Use the component name
 * @AS_SEARCH_TOKEN_MATCH_KEYWORD:		Use the component keyword
 * @AS_SEARCH_TOKEN_MATCH_ID:			Use the component ID
 *
 * The token match kind, which we want to be exactly 16 bits for storage
 * reasons.
 **/
typedef enum /*< skip >*/ __attribute__((__packed__)) {
	AS_SEARCH_TOKEN_MATCH_NONE	  = 0,
	AS_SEARCH_TOKEN_MATCH_MEDIATYPE	  = 1 << 0,
	AS_SEARCH_TOKEN_MATCH_PKGNAME	  = 1 << 1,
	AS_SEARCH_TOKEN_MATCH_ORIGIN	  = 1 << 2,
	AS_SEARCH_TOKEN_MATCH_DESCRIPTION = 1 << 3,
	AS_SEARCH_TOKEN_MATCH_SUMMARY	  = 1 << 4,
	AS_SEARCH_TOKEN_MATCH_KEYWORD	  = 1 << 5,
	AS_SEARCH_TOKEN_MATCH_NAME	  = 1 << 6,
	AS_SEARCH_TOKEN_MATCH_ID	  = 1 << 7,
	/*< private >*/
	AS_SEARCH_TOKEN_MATCH_LAST	  = 0xffff
} AsSearchTokenMatch;

typedef guint16 AsTokenType; /* big enough for both bitshifts */

void		as_component_complete (AsComponent *cpt, GPtrArray *icon_paths);

AS_INTERNAL_VISIBLE
GHashTable  *as_component_get_languages_table (AsComponent *cpt);

void	     as_component_set_bundles_array (AsComponent *cpt, GPtrArray *bundles);

gboolean     as_component_has_package (AsComponent *cpt);
gboolean     as_component_has_install_candidate (AsComponent *cpt);

const gchar *as_component_get_architecture (AsComponent *cpt);
void	     as_component_set_architecture (AsComponent *cpt, const gchar *arch);

GPtrArray   *as_component_generate_tokens_for (AsComponent *cpt, AsSearchTokenMatch token_kind);

void	     as_component_set_ignored (AsComponent *cpt, gboolean ignore);

AsOriginKind as_component_get_origin_kind (AsComponent *cpt);
void	     as_component_set_origin_kind (AsComponent *cpt, AsOriginKind okind);

gboolean     as_component_merge (AsComponent *cpt, AsComponent *source);
void as_component_merge_with_mode (AsComponent *cpt, AsComponent *source, AsMergeKind merge_kind);

gboolean as_component_load_from_xml (AsComponent *cpt,
				     AsContext	 *ctx,
				     xmlNode	 *node,
				     GError	**error);
xmlNode *as_component_to_xml_node (AsComponent *cpt, AsContext *ctx, xmlNode *root);

gboolean as_component_load_from_yaml (AsComponent *cpt,
				      AsContext	  *ctx,
				      GNode	  *root,
				      GError	 **error);
void	 as_component_emit_yaml (AsComponent *cpt, AsContext *ctx, yaml_emitter_t *emitter);

AS_END_PRIVATE_DECLS

#endif /* __AS_COMPONENT_PRIVATE_H */
