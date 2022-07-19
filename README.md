# VSH2-TemplateMaker

### Building project:
Use [premake5.lua](https://premake.github.io) to build the project.
---
### Usage:


Each templates are generated from a JSON file that are written as arguments while executing.

Example: `VSH2-TemplateMaker.exe generic.json some_other.json yet_another`.

---
#### Settings:
Check out `generic.json` for a sample.
###### name: name of the template to generate, note that will also be prefixed to every function that will generated.
###### callbacks: array of objects that will be processed.
---
##### file: relative file path to ouput.
##### forwards: callback's id from `vsh2.inc` .
##### return: return type (can only be `void` or `Action`).
##### args: list of arguments that the function will have.
##### extra: list of extra functions that might be useful.
---
###### is_boss: <target> : generate a check that validates if the target is a boss .
###### include: <path> : add the code that exists in the file to the body of the function.

##### include's tokens:
###### \<Name\>: unmodified boss' template name from the json file.
###### \<name\>: lower case verison of \<Name\>.
