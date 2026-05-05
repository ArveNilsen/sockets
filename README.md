# Kode for fagsamtale

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
