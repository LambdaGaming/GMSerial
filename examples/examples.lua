--Reads and prints out the output of the specified device.
function Serial_Test( port, baud )
	local ino = gmserial.Begin( port, baud )
	local str = ino:ReadString()
	print( str )
	ino:Close()
end

--[[
	DarkRP lockdown test:
	Used alongside ButtonInput.ino to detect when the button is pressed.
	Once pressed, the player will call a lockdown in the game (assuming they're mayor)
	Also demonstrates that you can use loops to constantly read outputs without
	initializing a new connection with every loop and causing insane lag/crashes.
]]
function Serial_Lockdown( port, baud )
	local ino = gmserial.Begin( port, baud )
	timer.Create( "SerialLockdown", 0.1, 0, function()
		local str = ino:ReadString()
		if isstring( str ) and string.find( str, "1" ) then
			LocalPlayer():ConCommand( "say /lockdown" )
			timer.Remove( "SerialLockdown" )
			ino:Close()
		end
	end )
end
