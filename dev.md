# gmserial.Begin( `String` port, `Number` baudrate )
## Description
 Initializes a new serial connection.
## Arguments
 `String` - Name of the port. You can get a list of valid names by calling `gmserial.ListDevices`.
 `Number` - Baudrate of the connection. Usually determined by the serial device.
## Returns
 `Serial` - Instance of the serial connection.
## Example
```lua
local device = gmserial.Begin( "COM3", 9600 )
```

# Serial:SetOutputDelay( `Number` delay )
## Description
 Sets the delay for outgoing data to the physical device.
## Arguments
 `Number` - Amount of seconds that the delay should last.

# Serial:SetInputDelay( `Number` delay )
## Description
 Sets the delay for incoming data from the physical device.
## Arguments
 `Number` - Amount of seconds that the delay should last.

# Serial:WriteString( `String` str )
## Arguments
 `String` - The string to write to the serial device.
## Returns
 `Number` - Number of bytes that were successfully written, or 0 if the connection was closed.
## Example
```lua
local device = gmserial.Begin( "COM3", 9600 )
device:WriteString( "test" )
```

# Serial:ReadString( `Number` size, `String` eol )
## Description
 Reads a single line until the size limit is reached or an end of line (eol) character is read.
## Arguments
 `Number` - Optional. Max size of the read string in bytes. Defaults to 65536.
 `String` - Optional. End of line character to detect. Defaults to \n.
## Returns
 `String` - The string that was read.
## Example
```lua
local device = gmserial.Begin( "COM3", 9600 )
print( device:ReadString() )
```

# Serial:IsConnected()
## Returns
 `Bool` - Whether or not the serial connection is open.

# Serial:Close()
## Description
 Closes the serial connection if it's open.
