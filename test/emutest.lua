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

    -- look for env var "EMUTEST_FB_CRC_PASS"
    if os.getenv("EMUTEST_FB_CRC_PASS") then
        -- if found, check for CRC match
        if get_fb_crc() == tonumber(os.getenv("EMUTEST_FB_CRC_PASS")) then
            print("Test passed via get_fb_crc.")
            screenshot(romname .. "-pass.png")
            os.exit(0)
        end
    end

    -- look for RAM signature
    if string.find(ram, 'TestPass') then
        print("Test passed via RAM signature.")
        run()
        print("FB_CRC=", get_fb_crc())
        screenshot(romname .. "-pass.png")
        os.exit(0)
    elseif string.find(ram, 'TestFail') then
        print("Test failed via RAM signature.")
        run()
        print("FB_CRC=", get_fb_crc())
        screenshot(romname .. "-fail.png")
        os.exit(1)
    end

end

print("Test indeterminate.")
print("FB_CRC=", get_fb_crc())
screenshot(romname .. "-unknown.png")
os.exit(2)
