# this script when compiled will create an htmlfile named map1.html shown at the last line which has multiple layers
# that color codes the map according to popularion along with location of cvolcanoes in north america.
# the attached fiels volcanoes.txt and world.json are the refferenced files. Found them online

import folium  #import library folium folium is a library that creates leaflet Maps
import pandas # install pandas linrary very powerful for data analysis used here to interprit the refferenced json and txt/csv files


data = pandas.read_csv("volcanoes.txt")   # load data into varible data for forloop to loop all the markers
lat = list(data["LAT"])
lon = list(data["LON"])
elev = list(data["ELEV"])


def color_produced(elevation):        # function that determins the color of the marker based on elevation of the volcano
    if elevation < 1000:
        return 'green'
    elif 1000 <elevation< 3000:
        return "orange"
    else:
        return "red"

map = folium.Map(location= [32,-122], zoom_start=6, tiles = "Stamen Terrain")
fgv = folium.FeatureGroup(name="Volcanoes")  # feature group marker is a feature. can add multiple features per object.


                                                    # use zip funtion to loop through iterables.
for lt, ln, el in zip(lat, lon, elev):               # loop for iterating throught the list since We dont want to add a marker for every location
    fgv.add_child(folium.CircleMarker(location=[lt,ln],radius=6,popup=str(el)+"m",fill_color=color_produced(el), fill=True, fill_opacity=0.7))

fgp = folium.FeatureGroup(name="Population")   # feature group layer for population


fgp.add_child(folium.GeoJson(data =open("world.json", 'r', encoding="utf-8-sig").read(),
style_function=lambda x:{'fillColor':"green" if x['properties']['POP2005'] < 10000000 else 'orange' if 10000000 <=x['properties']["POP2005"] < 20000000 else 'red'} ))
                                                    # if else function that determines the contries color based on population

map.add_child(fgv)  #make feature group  for Volanoes
map.add_child(fgp)  #make feature group for population
map.add_child(folium.LayerControl())         # layer control to turn feature groups on and off

map.save("Map1.html")  # save scrip as html file you can open once compiled
