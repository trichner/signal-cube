# Signal Cube

## Protocol

### Wire Format
The wire format for our little protocol is one
line of command terminated by a newline and
everything that follows is the command specific body.
```
<command>\n
<body>
```

* `command` shall be an all caps alphanumeric string
* `body` limited only by the underlying [particle API limitations](https://docs.particle.io/reference/device-os/firmware/photon/#particle-publish-)

#### Heartbeat Command
```
HEARTBEAT
<channel>
<status>
```

* `channel` shall be: `channel := 'chan' [0-9]+`, e.g. `chan0`
* `status` shall be: `status := 'up' | 'down'`

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

