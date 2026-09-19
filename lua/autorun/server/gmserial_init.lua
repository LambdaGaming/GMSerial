--Safely initialize the module
local version = "2.0"
hook.Add( "InitPostEntity", "SerialModuleInit", function()
	if !util.IsBinaryModuleInstalled( "gmserial" ) then
		MsgC( Color( 255, 0, 0 ), "\nERROR: GMSerial module not found.\n" )
		return
	end
	require( "gmserial" )
	MsgC( Color( 0, 255, 255 ), "\nGMSerial v"..version.." successfully loaded.\n" )
end )
