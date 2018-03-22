/* BareMetal File System Utility */
/* Written by Ian Seyler of Return Infinity */
/* v1.2.3 (2017 04 07) */

#ifndef BMFS_PATH_H
#define BMFS_PATH_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Used to walk a path without
 * allocated any memory or parsing
 * any strings.
 * */

struct BMFSPathVisitor
{
	/** Used to pass data to the callback functions.  */
	void *data;
	/** Called when a parent directory is parsed. */
	int (*visit_parent)(void *data, const char *name, uint64_t name_size);
	/** Called when the basename of the path is parsed. */
	int (*visit_basename)(void *data, const char *name, uint64_t name_size);
};

/** A path that references a file
 * or directory on the file system.
 * */

struct BMFSPath
{
	const char *String;
	uint64_t Length;
};

/** Initializes the path to an
 * empty string.
 */

void bmfs_path_init(struct BMFSPath *path);

/** Inidicates whether or not the path is
 * empty.
 * @param path An initialized path structure.
 * @returns One if the path is empty, zero if
 *  it is not.
 * */

int bmfs_path_empty(const struct BMFSPath *path);

/** Gets the root directory of the path.
 * If the path is already a root directory,
 * then @p root is an empty path.
 * @param path An initialized path structure.
 * @param root An uninitialized path structure.
 *  This function will set this parameter to the
 *  root directory of @p path.
 * @returns Zero if the root was found, a negative
 *  number if it wasn't.
 */

int bmfs_path_split_root(struct BMFSPath *path,
                         struct BMFSPath *root);

/** Sets the contents of the path.
 * @param path An initialized path structure.
 * @param string The string containing the path.
 *  The characters pointed to by this address may
 *  be modified by subsequent calls.
 * @param length The length of @p string. This
 *  should not include the null-terminator, if
 *  there is one.
 */

void bmfs_path_set(struct BMFSPath *path,
                   const char *string,
                   uint64_t length);

/** Parses the path and calls the visitor
 * function everytime that it matches a parent
 * directory or the basename of the path.
 * This is used for opening or creating files
 * and directories.
 * @param path The path to visit.
 * @param visitor The visitor to call for each
 * path component.
 * @returns Zero if the path is visited entirely
 * without an error from the visitor. If non-zero
 * is returned, it is returned from the visitor.
 * */

int bmfs_path_visit(struct BMFSPath *path,
                    struct BMFSPathVisitor *visitor);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* BMFS_PATH_H */

