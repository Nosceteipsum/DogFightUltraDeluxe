//-----------------------------------------------------//
//						       //
// 		DOG FIGHT ULTRA DELUXE		       //
//  						       //
//  Made By: Tommy Kobberø Andersen		       //
//  						       //
//  Date:    Feb. 2003				       //
//  						       //
//-----------------------------------------------------//

//--- Options ---//

FPS-ON:           [F1]
FPS-OFF:          [F2]
Packets_Count-On  [F3]
Packets_Count_Off [F4]
Ping-On	          [F5]
Ping-Off          [F6]
CBOT-ON:          [F7]
CBOT-OFF:         [F8]

//--- Controls ---//

Plane:
Plane Speed:  [UP]
Plane Right:  [RIGHT]
Plane Left:   [LEFT]
Plane Shot:   [SPACE]
Plane Spec:   [CTRL]
Plane Para:   [E]

Man:
MoveMan Left: [LEFT]
MoveMan Right:[RIGHT]
MoveGun Left: [DOWN] 
MoveGun RIGHT:[UP]
ManFire:      [SPACE]
ManSpec:      [CTRL]

//--- BuyRound ---//

300 Money Per round
100 Money if not dead
 75 Money Per hits

Max: 5000 Money

Plane Stuff:
 500: Faster Plane 
 800: Stealth
1000: Extra Amour
1400: Faster Turn-Around

Para Stuff:
 400: Faster Para
 700: AutoPilot
1000: Stealth
1500: Escape Sphere

Primary Fire:
 300: Faster  Shoot
 500: Stealth Shoot
1000: Fire Shoot(double damage)
2000: Remote Explosion (Explose on Key-Release)

Spec Fire:

 400: Drugs
 600: Invert Controls
 900: Blind
1600: Eject (Player Eject on hit if possible)

//--- Version ---//

1.00: 
DFUD official release.

1.01: 
Client/Server Network-read method fixed.
spec(invert controls) fixed.

1.02:
Packets count option.
Clients get a message when the server disconnet.
Sync Array size fixed.

1.03:
Sync default value 180.
WinSock Engine updated.
Allow to buy everything in all category.
Decrease (P-Fire: Faster-Shoot) speed.
Increase (S-Fire: Decrease-Speed) effect.

1.04:
Server calculate clients ping time.
Show Ping-Time option (Server side only).
Hits/Money are resetted when player quit the game.
Clients/Server Keys-Packet size decreased to gain more speed.
Collision with tree on ice-map fixed.
Client Buy-Equip Packets Spam fixed.
Speed Decrease and rotating on para collision removed.

1.05:

Added 4 new weapons:
-Plane: 1400: Faster Turn-Around
-Para:  1500: Escape Sphere
-Fire:  2000: Remote Explosion
-Spec:  1600: Eject

Money limit increased to 2000.
Replaced (S-Fire: Decrease-Speed) with drugs effect.
Replaced current Ping-Timer with a High-resolution Counter.
Packets Log-file generated to help debugging network problems.
Changed the order of F1-F8.
Server tells the clients if para is used (To avoid 'Out of Sync' problems).
Changed the network code to make a short sync with a key packet.
Fixed strange behavior with the skies.
Sound when Plane hit explosion.

1.06

Removed Key-Packet. So Sync-Packet have all power...
Removed Ping-Packet to gain speed.
Removed bot.
Syns packet hold key-packet now.
Sync default value 100. (Refresh 10 time in 1 second)

1.07

Automatic Sync_value.
It's now possible to see ping time again.
Added bot again (take control of your own plane now. To debug use)

1.09 unofficial release

Weapon balanced(Escape Sphere), Automatic jump out when plane explodes.
When plane explodes, player is automatic ejected.
Corrected disconnect problem.
Max money limit incresead to 5000 from 2000
Money per round changed to 300 from 200
Money if not dead changed to 100 from 50
Money per hits changed to 75 from 25
Sound disabled, sorry...
Fixed collision on lower part on man
Man collision Bigger

//--- Contacts ---//

To contact me use this:

email: Dogfight@logicwork.net
icq: 64049683

http://logicwork.net
http://logicwork.dk
