function entries( arg ) -- iterator
    return function()
        return arg:pop()
    end
end

for i in entries( list_container ) do
    io.write( "From LUA:  ", i, "\n" )
end

for i = 1, 10 do
    list_container:push( 50 + i * 100 )
end