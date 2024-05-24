load("os")

// Define the function to execute shell commands
function runCmd(cmd) {
   	print(cmd);
    os.exec(cmd);
}

// Array to hold targets
var targets = [];

// Function to build the command string from target arguments
function buildStr(target) {
    var selectedTarget = "";
    for (var argId = 2; argId < target.length; argId++) {
        selectedTarget += target[argId] + " ";
    }
    return selectedTarget.trim();
}

// Target constructor function
function Target(name, dependsOn, fn, description) {
    this.name = name;
    this.dependsOn = dependsOn;
    this.fn = fn;
    this.description = description || "target for " + name;
    this.exec = function () {
        try {
            this.fn();
        } catch (e) {
            print(e);
        }
    };
    targets.push(this);
}

// Define targets
new Target("rocket executable", [], function () {
   	print("Compiling rocketExec...");
    runCmd("g++ main.cpp -o bin/rocket -llua -llua++ -lraylib");
}, "rocketExec, or rocket, is a C++ executable that wraps a lot of functionality on top of Lua");

new Target("rocket example lib", ["rocket executable"], function () {
   	print("Compiling example libs...");
    runCmd("g++ libs/example.cpp -o bin/example.so -shared -fPIC -llua -llua++");
}, "compiles the example lib for the rocket executable");

new Target("all",["rocket executable", "rocket example lib"],function(){},"builds everything")
new Target("install",["all"],function(){
    runCmd("mkdir -p ~/bin");
    runCmd("cp bin/rocket ~/bin/rocket");
},"installs rocketExec as rocket")

new Target("help", [], function () {
   	print("Usage: powerjs build.js [target]");
   	print("Targets:");
    targets.forEach(function (target) {
       	print("- " + target.name);
       	print(" ^- " + target.description);
        target.dependsOn.forEach(function (dep) {
           	print("  ^- depends On: " + dep + ".");
        });
       	print("");
    });
    quit(0);
}, "Shows a help message");

// Extract selected target from command line arguments
var selectedTarget = buildStr(powerjs.args);

// Find and execute the selected target
var targetFound = false;
function build(selectedTarget) {
	targets.forEach(function (target) {
		if (target.name === selectedTarget) {
			if (target.dependsOn.length > 0) {
				target.dependsOn.forEach(function (dep) {
					if (!targetFound) {
						build(dep);
					}
				})
			}
			target.exec();
			targetFound = true;
		}
	})
}
build(selectedTarget);
