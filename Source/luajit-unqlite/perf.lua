unqlite = require "src/unqlite"

local function go(dbname)
	os.execute("rm -rf " .. dbname)
	local N = 1000000
	local start = os.clock()

	local db = unqlite.open(dbname)
	for i = 1, N do
		local v = tostring(i)
		assert(db:set(v, v))
		--//who needs to fsync? not us
		--if (i % 1000) == 0 then
		--	db:commit()
		--end
	end
	local write_time = N/(os.clock() - start)
	db:commit()

	start = os.clock()
	for i = 1, N do
		local v = tostring(i)
		assert(db:get(v) == v)
	end
	local read_time = N/(os.clock() - start)

	assert(db:close())

	return write_time, read_time
end

local w, r
w, r = go("perf.db") -- jit prime
w, r = go("perf.db")
print ("Write time: " .. w .. " ops/sec")
print ("Read time: " .. r .. " ops/sec")
