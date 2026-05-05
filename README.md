# Kode for fagsamtale

## Hva og hvorfor?
Mange eksempler på bruk av Sockets API fokuserer på å gruppere sammen riktige system kall.
Her velger jeg heller å fokusere på data typer. Målet er små, men meningsfulle verdi-typer som kan gi et mer selvforklarende API. Verdi-typene er tenkt å ha standard layout og være testbare. 

## Bygginstrukser
Fra rot:
<pre>
<code>
cmake -G "Ninja" -B build -S .
ninja -C build
</code>
</pre>

Ninja kan byttes ut med feks Make.

Full test kjøres slik, fra rot:
<pre>
<code>
ctest --test-dir build/test
</code>
</pre>
