unqlite = require "src/unqlite"

TEST_DB_NAME = "test.db"
TEST_KEY = "test"
TEST_VALUE = "Hello world"

function test_set_simple()
	local db = unqlite.open(TEST_DB_NAME)
	assert(db:set(TEST_KEY, TEST_VALUE))
	assert(db:get(TEST_KEY) == TEST_VALUE)
	assert(db:close())
end

function test_append_simple()
	local db = unqlite.open(TEST_DB_NAME)
	assert(db:set(TEST_KEY, "Hello"))
	assert(db:append(TEST_KEY, " "))
	assert(db:append(TEST_KEY, "world"))
	assert(db:get(TEST_KEY) == TEST_VALUE)
	assert(db:close())
end

function test_delete_simple()
	local db = unqlite.open(TEST_DB_NAME)
	assert(db:set(TEST_KEY, TEST_VALUE))
	assert(db:get(TEST_KEY) == TEST_VALUE)
	assert(db:delete(TEST_KEY))
	assert(db:get(TEST_KEY) == nil)
	assert(db:close())
end

function test_rollback_simple()
	local db = unqlite.open(TEST_DB_NAME)
	assert(db:delete(TEST_KEY))
	assert(db:get(TEST_KEY) == nil)
	assert(db:commit())

	assert(db:begin())
	assert(db:set(TEST_KEY, TEST_VALUE))
	assert(db:get(TEST_KEY) == TEST_VALUE)
	assert(db:rollback())
	assert(db:get(TEST_KEY) == nil)

	assert(db:close())
end

function test_cursor()
	local db = unqlite.open(TEST_DB_NAME)
	assert(db:delete(TEST_KEY))

	for i = 0, 20 do
		assert(db:set(TEST_KEY .. i, TEST_VALUE))
	end

	local cur = db:cursor()

	local c = 0
	assert(cur:first())
	while cur:next_entry() do
		local k = cur:key()
		assert(k)
		local d = cur:data()
		assert(d == TEST_VALUE)
		c = c + 1
	end

	assert(cur:release())
	assert(c >= 20)

	assert(db:close())
end

function test_gc()
	local f = function()
		local db = unqlite.open(TEST_DB_NAME)
		assert(db:append(TEST_KEY, TEST_VALUE))
	end

	local db = unqlite.open(TEST_DB_NAME)
	assert(db:delete(TEST_KEY))
	db:close()
	f()
	collectgarbage()
	f()
	collectgarbage()
	f()
	collectgarbage()
	db = unqlite.open(TEST_DB_NAME)
	assert(db:get(TEST_KEY) == TEST_VALUE .. TEST_VALUE .. TEST_VALUE)
	assert(db:close())
end

local db = unqlite.open(TEST_DB_NAME)
for k, v in pairs(_G) do
	if k:sub(1, 5) == "test_" then
		print ("Running: " .. k)
		v()
		collectgarbage()
	end
end

print ("Success")
