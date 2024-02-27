# Uno

## Client

Das Frontend, das sich um zu spielen auf das Backend als verbindet. Nutzt standardmäßig ws://localhost:8888 als Addresse.

## Server

Das Backend mit der gesamten Spiellogik. Hostet einen Websocket, auf den sich die Clients verbinden können.

## Shared

Enthälte geteilte Klassen, die sowohl vom Front-, als auch Backend genutzt werden. Beispielsweiße die Unokarten inklusive der JSON funktionalität.
