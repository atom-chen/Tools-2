========
Overview
========

luajit-unqlite is a luajit ffi binding allowing you access to UnQLite
within the awesome luajit.

UnQLite is an "in-process software library which implements a self-contained,
serverless, zero-configuration, transactional NoSQL database engine."
See more at http://unqlite.org/

These bindings were originally written to support an on-disk persistance
layer for a love2d game, but should be useful in other contexts.

Also it has tests.


Beta Warning
=============

This is in beta. So while I hope you use it, it may delete
your data or kill your babies.  Be warned, please submit bug reports
on the project bitbucket.


Dependencies
============

luajit and UnQLite


Features
========

These bindings provide access to the key-value store, transactions,
and cursors.  There are no plans on implementing Jx9 support, but
patches are surely welcomed.

Usage
=====

Copy ``src/unqlite.lua`` somewhere in your lua path, and compile
either ``libunqlite.so`` or ``unqlite.dll`` depending on your OS.
(The supplied versions may or may not work on your system).

::

    unqlite = require "unqlite"

    -- open db
    db = unqlite.open("test.db")

    -- kv basics
    db:set("test", "Hello world")
    db:get("test")
    -- "test"
    db:delete("test")
    db:get("test")
    -- nil


See ``test.lua`` for examples on transaction and cursor usage.


Future Features
===============

  * expose functionality of unqlite_config
  * better/more idiomatic lua error reporting


License
=======


This binding is released under the 2-Clause BSD license.  See
``LICENSE.txt``.  This is the same license that UnQLite uses.

The included ``libunqlite.so`` and ``unqlite.dll`` are just compiled
versions of unqlite in case that helps anyone.  UnQLite is released
under the same 2-Clause BSD license.  See ``LICENSE_unqlite.txt``.


Contributors
============

  * `Shu Zong Chen`_

.. CONTRIBUTORS

.. _`Shu Zong Chen`: http://freelancedreams.com/
