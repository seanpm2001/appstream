v1.0 API Todo List
==================

This document exists to list all items that have to be worked on for the
libappstream API break for the AppStream 1.0 release.


## TODO

 * Sort out the various markup-to-text conversion functions, make some of them public API and maybe rewrite some
   (there are likely some performance improvements to be found there)

 * Review all public API


## DONE (kept for reference)

 * Remove all deprecated API

 * Don't expose raw GPtrArray / GHashTable with automatic free functions in public API
   that is consumed by language bindings. See https://gitlab.gnome.org/GNOME/gobject-introspection/-/issues/305#note_1010673
   for details.

 * Possibly drop the as_component_get_active_locale / component-specific locale overrides, and only expose on AsContext
   instead that is always present to reduce the API complexity.

 * Drop use of `/etc/appstream.conf`, expose any of its remaining options (if there are any) as C API
   for client tools to use.

 * Cleanup AsPool API, only keep sensible functions (maybe make the pool read-only?)

 * Simplify AsValidator API to make an obvious decision for API users whether validation failed, passed or wasn't possible due to other errors.
   (at the moment this is all somewhat combined together, and usable but not obvious)

 * Review AsContext enums

 * Either drop AsDistroInfo or rename it to AsOSInfo (depending on whether it's still needed)

 * Make UNKNOWN the first entry in AsFormatVersion enum

 * Rename AsPoolFlags: e.g. AS_POOL_FLAG_READ_COLLECTION -> AS_POOL_FLAG_USE_OS_COLLECTION

 * Store `keywords` in a GPtrArray instead of GStrv, so adding and removing them is more efficient. Consider not using a
   GHashTable for locale->keywords mapping to reduce memory usage (as often we will only have very few locale and need them rarely)

 * AS_FORMAT_STYLE_COLLECTION -> AS_FORMAT_STYLE_CATALOG

 * Drop AS_IMAGE_LARGE_HEIGHT & Co, they are now misleading and less useful than when we had stricter image dimensions

 * Create new AsReleaseData/AsReleases to hold external release information

 * Make AsMetadata use AsReleases

 * Drop all bytes+length uses in public API and use GBytes instead if a function takes byte arrays

 * Make AsComponentBox/AsReleases available for the Qt bindings
