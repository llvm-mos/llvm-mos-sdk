load_core(corepath)
load_game(rompath)

-- function to extract filename from path
function get_filename(path)
    local result = path
    -- iterate thru chars
    for i=1,string.len(path) do
        -- if char is a slash
        if string.sub(path, i, i) == "/" then
            -- return substring from next char to end
            result = string.sub(path, i+1, string.len(path))
        end
    end
    return result
end

romname = get_filename(rompath)
print("Running test on", romname)

print(get_logs())

for i=1,1000 do

    run()

    local ram = get_ram()

    if string.find(ram, 'TestPass') then
        print("Test passed.")
        print("CRC", get_fb_crc())
        run()
        screenshot(romname .. "-pass.png")
        os.exit(0)
    elseif string.find(ram, 'TestFail') then
        print("Test failed.")
        run()
        screenshot(romname .. "-fail.png")
        os.exit(1)
    end

end

print("Test indeterminate.")
screenshot(romname .. "-unknown.png")
os.exit(2)
