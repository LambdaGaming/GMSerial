WireToolSetup.setCategory( "Chips, Gates", "Advanced" )
WireToolSetup.open( "serial", "Serial", "gmod_wire_serial", nil, "Serial" )

if CLIENT then
	language.Add( "tool.wire_serial.name", "Serial Device" )
	language.Add( "tool.wire_serial.desc", "Transmits to and receives data from a real serial device." )
	language.Add( "tool.wire_serial.0", "Left Click: Spawn device." )
	WireToolSetup.setToolMenuIcon( "icon16/wrench.png" )
end

WireToolSetup.SetupMax( 5 )

if SERVER then
	function TOOL:GetConVars()
		return self:GetClientNumber( "StartEnabled" ), self:GetClientInfo( "Port" ), self:GetClientInfo( "Baudrate" ), self:GetClientInfo( "model" ), self:GetClientNumber( "NumFix" ), self:GetClientNumber( "Timeout" )
	end

	function TOOL:LeftClick_PostMake( ent, ply, trace )
		if ent == true then return true end
		if ent == nil or ent == false or !IsValid( ent ) then return false end

		ent:GetPhysicsObject():EnableMotion( false )
		undo.Create( self.WireClass )
		undo.AddEntity( ent )
		undo.SetPlayer( ply )
		undo.Finish()
		ply:AddCleanup( self.WireClass, ent )
		return true
	end
end

function TOOL:SetPos( ent, trace )
	ent:SetPos( trace.HitPos )
end

TOOL.ClientConVar = {
	StartEnabled = 1,
	Port = "COM3",
	Baudrate = 9600,
	model = "models/bull/gates/microcontroller2.mdl",
	NumFix = 0,
	Timeout = 1000
}

function TOOL.BuildCPanel( panel )
	WireToolHelpers.MakePresetControl( panel, "wire_serial" )
	panel:CheckBox( "Start Enabled", "wire_serial_StartEnabled" )
	panel:CheckBox( "Convert Inputs To Numbers", "wire_serial_NumFix" )
	panel:TextEntry( "Serial Port Name", "wire_serial_Port" )
	panel:NumberWang( "Baudrate", "wire_serial_Baudrate", 0, 1000000, 0 )
	panel:NumberWang( "Timeout", "wire_serial_Timeout", 0, 10000, 0 )
	WireDermaExts.ModelSelect( panel, "wire_serial_model", list.Get( "Wire_gate_Models" ), 2 )
end
