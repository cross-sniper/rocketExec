-- Define a function to execute shell commands
local function runCmd(cmd)
    print(cmd)
    local result, reason, code = os.execute(cmd)

    if result == nil or result == false or code ~= 0 then
        print("Command failed: " .. (reason or "unknown") .. " with code " .. (code or "unknown"))
        os.exit(1)
    end
end

local function fileModified(filename)
    local f = io.popen("stat -c %Y " .. filename)
    local modifiedTime = f:read("*a")
    f:close()
    return tonumber(modifiedTime)
end

local function needsRebuild(source, target)
    local sourceTime = fileModified(source)
    local targetTime = fileModified(target)
    return sourceTime and targetTime and sourceTime > targetTime
end

local function isDirectory(path)
    local cmd = "test -d " .. path .. " && echo yes || echo no"
    local handle = io.popen(cmd)
    local result = handle:read("*a"):gsub("%s+", "") -- Trim whitespace
    handle:close()
    return result == "yes"
end

local function getFilesRecursively(dir)
    local files = {}
    
    local function traverseDirectory(currentDir)
        local handle = io.popen("ls -A1 " .. currentDir)
        local listing = handle:read("*a")
        handle:close()
        
        for file in listing:gmatch("[^\r\n]+") do
            local filePath = currentDir .. "/" .. file
            if isDirectory(filePath) then
                traverseDirectory(filePath)
            else
                table.insert(files, filePath)
            end
        end
    end
    
    traverseDirectory(dir)
    return files
end

local function directoryNeedsRebuild(sourceDir, target)
    local targetTime = fileModified(target)
    for _, file in ipairs(getFilesRecursively(sourceDir)) do
        if fileModified(file) > targetTime then
            return true
        end
    end
    return false
end

-- Array to hold targets
local targets = {}

local function buildStr(target)
    local selectedTarget = ""
    for argId = 1, #target do
        selectedTarget = selectedTarget .. target[argId]
        if not (argId + 1) == #target then selectedTarget = selectedTarget .. " " end
    end
    return selectedTarget
end

local function build(selectedTarget)
    for _, target in ipairs(targets) do
        if target.name == selectedTarget then
            target.exec()
        end
    end
end

local function Target(name, dependsOn, fn, description)
    local self = {}
    self.name = name
    self.dependsOn = dependsOn
    self.fn = fn
    self.description = description or "target for " .. name
    self.exec = function()
        for _, dep in ipairs(self.dependsOn) do
            build(dep)
        end
        local success, err = pcall(self.fn)
        if not success then
            print(err)
        end
    end

    table.insert(targets, self)
    return self
end

-- Define targets
Target("rocket executable", {"fs.so", "raylib.so"}, function()
    if needsRebuild("main.cpp", "bin/rocket") then
        print("Compiling rocketExec...")
        runCmd("g++ main.cpp -o bin/rocket -llua -llua++ -lraylib")
    end
end, "rocketExec, or rocket, is a C++ executable that wraps functionality on top of Lua")

Target("raylib.so", {}, function()
    if directoryNeedsRebuild("libs/raylib/", "bin/raylib.so") then
        print("Compiling raylib.so...")
        runCmd("g++ libs/raylib/raylib.cpp -o bin/raylib.so -shared -fPIC -llua -llua++ -lraylib")
    end
end, "Compiles the raylib.so that you can use with default Lua")

Target("fs.so", {}, function()
    if needsRebuild("libs/fs/fs.cpp", "bin/fs.so") then
        print("Compiling fs.so...")
        runCmd("g++ libs/fs/fs.cpp -o bin/fs.so -shared -fPIC -llua -llua++")
    end
end, "Compiles the fs.so that you can use with default Lua")

Target("all", {"rocket executable"}, function()
    -- Placeholder function, as per the original code
end, "Builds everything")

Target("install", {"all"}, function()
    runCmd("mkdir -p ~/bin")
    runCmd("cp bin/rocket ~/bin/rocket")
end, "Installs rocketExec as rocket")

Target("clean", {}, function()
    print("Cleaning build artifacts...")
    runCmd("rm -rf bin/*")
end, "Removes all built files from the bin directory")

Target("help", {}, function()
    print("Usage: [lua/rocket] build.lua [target]")
    print("Targets:")
    for _, target in ipairs(targets) do
        print("- " .. target.name)
        print(" ^- " .. target.description)
        for _, dep in ipairs(target.dependsOn) do
            print("  ^- depends On: " .. dep .. ".")
        end
        print("")
    end
end, "Shows a help message")

local selectedTarget = buildStr(arg)

build(selectedTarget)

-- this is just so rocketExec(rocket) doesn't error out due to no main function being found
function main()
end
