# MicroViewer backend
Prosty backend do wysyłania danych do aplikacji mobilnej.

### Budowanie
Do kompilacji trzeba:
- cmake
- meson
- gmock-devel

Lub odpowiedników dla innych dystrybucji.

### Docker

Należy wykonać:

```
docker build . -t microviewer/backend && docker save microviewer/backend > image.tar
```
Aby wgrać na TrueNAS scale:
1. skopiować obraz na NAS
2. docker load -i <ścieżka>/<nazwa obrazu>.tar
3. jako obraz podać microviewer/backend
4. dodać custom app z mapowanym portem 9080
5. gotowe, można sprawdzić requestem na <adres>:9080