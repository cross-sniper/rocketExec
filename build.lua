-- Define a function to execute shell commands
local function runCmd(cmd)
    print(cmd)
    os.execute(cmd)
end

-- Array to hold targets
local targets = {}

-- Function to build the command string from target arguments
local function buildStr(target)
    print(target[1])
    local selectedTarget = ""
    for argId = 1, #target do
        selectedTarget = selectedTarget .. target[argId]
        if not (argId + 1) == #target then selectedTarget = selectedTarget .. " " end
    end
    return selectedTarget
end

-- Target constructor function
local function Target(name, dependsOn, fn, description)
    local target = {
        name = name,
        dependsOn = dependsOn,
        fn = fn,
        description = description or "target for " .. name,
        exec = function()
            local success, err = pcall(fn)
            if not success then
                print(err)
            end
        end
    }
    table.insert(targets, target)
    return target
end

-- Define targets
Target("rocket executable", {}, function()
    print("Compiling rocketExec...")
    runCmd("g++ main.cpp -o bin/rocket -llua -llua++ -lraylib")
end, "rocketExec, or rocket, is a C++ executable that wraps functionality on top of Lua")

Target("rocket example lib", {"rocket executable"}, function()
    print("Compiling example libs...")
    runCmd("g++ libs/example.cpp -o bin/example.so -shared -fPIC -llua -llua++")
end, "compiles the example lib for the rocket executable")

Target("raylib.so", {}, function()
    print("Compiling raylib.so...")
    runCmd("g++ libs/raylib.cpp -o bin/raylib.so -shared -fPIC -llua -llua++ -lraylib")
end, "compiles the raylib.so that you can use with default lua")

Target("fs.so", {}, function()
    print("Compiling fs.so...")
    runCmd("g++ libs/fs/fs.cpp -o bin/fs.so -shared -fPIC -llua -llua++")
end, "compiles the fs.so that you can use with default lua")

Target("all", {"rocket executable", "rocket example lib"}, function()
    -- Placeholder function, as per the original code
end, "builds everything")

Target("install", {"all"}, function()
    runCmd("mkdir -p ~/bin")
    runCmd("cp bin/rocket ~/bin/rocket")
end, "installs rocketExec as rocket")

Target("help", {}, function()
    print("Usage: powerjs build.js [target]")
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

-- Extract selected target from command line arguments
local selectedTarget = buildStr(arg)

-- Find and execute the selected target
local targetFound = false
local function build(selectedTarget)
    for _, target in ipairs(targets) do
        if target.name == selectedTarget then
            if #target.dependsOn > 0 then
                for _, dep in ipairs(target.dependsOn) do
                    if not targetFound then
                        build(dep)
                    end
                end
            end
            target.exec()
            targetFound = true
        end
    end
end
build(selectedTarget)
function main()
end

