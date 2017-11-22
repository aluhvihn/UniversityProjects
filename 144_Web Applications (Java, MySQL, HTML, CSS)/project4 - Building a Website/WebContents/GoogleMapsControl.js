function init() {
    if (latitude == null || longitude == null) {
        getGeocode(address);
    } else {
        var coord = {lat: ""+latitude, lng: ""+longitude};
        getMap(coord);
    }
}

function getGeocode(address) {
    geocoder = new google.maps.Geocoder();
    geocoder.geocode( { 'address': address}, function(results, status) {
        if (status != google.maps.GeocoderStatus.OK) {
            showGlobe();
        } else {
            var location = results[0].geometry.location;
            getMap({lat:location.lat(), lng:location.lng()});
        }
  });
}

function getMap(coord) {
    var latlng = new google.maps.LatLng(coord.lat, coord.lng);
    var myOptions = {
        zoom: 14,
        center: latlng,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    var map = new google.maps.Map(document.getElementById("map-canvas"), myOptions);
    var marker = new google.maps.Marker({
        map: map,
        position: latlng
    });
    console.log(latlng);
}

function showGlobe() {
    var myOptions = {
        zoom: 1,
        center: new google.maps.LatLng(0, 0),
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    var map = new google.maps.Map(document.getElementById("map-canvas"), myOptions);
}

google.maps.event.addDomListener(window, "load", init);