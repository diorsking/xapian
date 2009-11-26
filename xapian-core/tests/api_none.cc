/** @file api_none.cc
 * @brief tests which don't need a backend
 */
/* Copyright (C) 2009 Richard Boulton
 * Copyright (C) 2009 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <config.h>

#include "api_none.h"

#include <xapian.h>

#include "apitest.h"
#include "testsuite.h"
#include "testutils.h"

using namespace std;

// Regression test: various methods on Database() used to segfault or cause
// division by 0.  Fixed in 1.1.4 and 1.0.18.  Ticket#415.
DEFINE_TESTCASE(nosubdatabases1, !backend) {
    Xapian::Database db;
    TEST_EQUAL(db.get_metadata("foo"), std::string());
    TEST_EQUAL(db.metadata_keys_begin(), db.metadata_keys_end());
    TEST_EXCEPTION(Xapian::DocNotFoundError, db.termlist_begin(1));
    TEST_EQUAL(db.allterms_begin(), db.allterms_end());
    TEST_EQUAL(db.allterms_begin("foo"), db.allterms_end("foo"));
    TEST_EXCEPTION(Xapian::DocNotFoundError, db.positionlist_begin(1, "foo"));
    TEST_EQUAL(db.get_lastdocid(), 0);
    TEST_EXCEPTION(Xapian::DocNotFoundError, db.get_doclength(1));
    TEST_EXCEPTION(Xapian::DocNotFoundError, db.get_document(1));
    return true;
}
