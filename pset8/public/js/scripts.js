/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
let map;
// markers for map
let markers = [];
//remember last marker for close window instead of reopening
let prevMarker = false;
// info window
let info = new google.maps.InfoWindow();
let news = [];
let newsStart = 0;
let newsLimit = 5;

// execute when the DOM is fully loaded
$(function () {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    let styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                { visibility: "off" }
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                { visibility: "off" }
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    let options = {
        center: { lat: 42.3770, lng: -71.1256 },
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    let canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

function getMarkerClickHandler(marker) {
    return () => {
        if (prevMarker == marker) {
            if (isInfoWindowOpen()) {
                hideInfo();
            } else {
                info.open(map, marker);
            }
        } else {
            hideInfo();
            info.setContent("<div id='info'><img alt='loading' src='img/ajax-loader.gif'/><div>");
            info.open(map, marker);
            newsStart = 0;
            loadArticles(marker.postal_code, refreshInfowindowData);
        }
        prevMarker = marker;
    };
}

function addMarker(place) {
    let myLatlng = new google.maps.LatLng(place.latitude, place.longitude);
    let marker = new google.maps.Marker({
        position: myLatlng,
        title: place.place_name,
        postal_code: place.postal_code,
    });
    marker.addListener("click", getMarkerClickHandler(marker));
    marker.setMap(map);
    markers.push(marker);
}

/**
 * Configures application.
 */
function configure() {
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function () {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function () {
        update();
    });


    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
        {
            source: search,
            templates: {
                empty: "<p class='tip'>No places found yet</p>",
                suggestion: _.template("<p class='tip'><%- place_name %>, <%- admin_name1 %>, <%- postal_code %></p>")
            }
        });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function (eventObject, suggestion, name) {

        // ensure coordinates are numbers
        let latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        let longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({ lat: latitude, lng: longitude });

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function (eventData) {
        hideInfo();
    });

    document.addEventListener("contextmenu", function (event) {
        event.returnValue = true;
        if (event.preventDefault != undefined)
            event.preventDefault();
        if (event.stopPropagation != undefined)
            event.stopPropagation();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

function hideInfo() {
    newsStart = 0;
    info.close();
}

function removeMarkers() {
    markers.forEach(marker => {
        marker.setMap(null);
    });
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb) {
    // get places matching query (asynchronously)
    let parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
        .done(function (data, textStatus, jqXHR) {
            // call typeahead's callback with search results (i.e., places)
            cb(data);
        })
        .fail(function (jqXHR, textStatus, errorThrown) {
            console.log(errorThrown.toString());
        });
}

/**
 * Updates UI's markers.
 */
function update() {
    // get map's bounds
    let bounds = map.getBounds();
    let ne = bounds.getNorthEast();
    let sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    let parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
        .done(function (data, textStatus, jqXHR) {
            removeMarkers();
            for (let i = 0, len = data.length; i < len; i++) {
                addMarker(data[i]);
            }
        })
        .fail(function (jqXHR, textStatus, errorThrown) {
            console.log(errorThrown.toString());
        });
}

function loadArticles(geo, cb) {
    let parameters = {
        geo: geo
    };
    $.getJSON("articles.php", parameters)
        .done(function (data, textStatus, jqXHR) {
            cb(data);
        })
        .fail(function (jqXHR, textStatus, errorThrown) {
            cb([]);
        });
}

function getInfowindowContent(data, start) {
    let content = "<ul class='info-list'>";
    for (let i = start, len = data.length; i < len && i < start + newsLimit; i++) {
        const article = data[i];
        content += `<li><a href='${article.link}' target='_blank'>${article.title}</a></li>`;
    }
    content += "</ul>"
    if (data.length > start + newsLimit) {
        content += "<button onclick='moreNews()' type='button' class='btn btn-primary info-list-btn'>More</button>";
    } else {
        content += "<button onclick='hideInfo()' type='button' class='btn btn-danger info-list-btn'>Close</button>";
    }
    return content;
}

function refreshInfowindowData(data, start = 0) {
    news = data;
    let content = getInfowindowContent(data, start);
    info.setContent(content);
}

function moreNews() {
    if (newsStart < news.length - newsLimit) {
        newsStart += newsLimit;
    } else {
        newsStart = 0;
    }
    if (info) {
        refreshInfowindowData(news, newsStart);
    }
}

function isInfoWindowOpen() {
    let map = info.getMap();
    return (map !== null && typeof map !== "undefined");
}