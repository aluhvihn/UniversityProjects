<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
    <head>
        <title>Item Search</title>
        <link href="bootstrap.min.css" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script src="bootstrap.min.js"></script>
        <script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script> 
        <c:if test="${not empty item}">
            <script type="text/javascript">
                var latitude = ${item.location.latitude};
                var longitude = ${item.location.longitude};
                var address = '${item.address}';
            </script>
            <script type="text/javascript" src="GoogleMapsControl.js"></script>
        </c:if>
    </head>

    <body>
        <nav class="navbar navbar-default" style="background: #ff8080;">
           <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
               <ul class="nav navbar-nav">
                   <li><a href="search" style="color: white;">Search</a></li>
                   <li><a href="item" style="color: white;">Item</a></li>
               </ul>
           </div>
        </nav>

        <div class="content-wrapper col-xs-12">
            <div class="row">
                <div class="col-xs-12">
                    <form action="item" method="GET" id="itemForm">
                        <div class="input-group">
                            <input type="text" class="form-control" name="itemID" placeholder="ItemID">
                            <span class="input-group-btn">
                                <button class="btn" type="submit">Search</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
            <c:choose>
                <c:when test="${not empty item}">
                    <div class="panel panel-info">
                        <div class="panel-heading">${item.name}</div>
                        <div class="panel-body">
                            <div class="row">
                                <span class="col-xs-6">
                                    <div id="map-canvas" style="width: 100%; height: 300px;"></div>
                                </span>
                                <div class="col-xs-6">
                                    Seller: ${item.seller.userID} <span class="badge">${item.seller.rating}</span><hr>
                                    Started: ${item.started}<br>
                                    Ends: ${item.ends}<br>
                                    Current: ${item.currently}<br>
                                    <div class="btn-group">
                                        <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-expanded="false">
                                        ${item.numberOfBids} Bidders <span class="caret"></span></button>
                                        <c:if test="${item.numberOfBids > 0}">
                                            <ul class="dropdown-menu" role="menu">
                                                <div class="list-group">
                                                    <c:forEach var="bid" items="${item.bids}">
                                                        <a href="#" class="list-group-item">
                                                            <p class="list-group-item-heading">${bid.bidder.userID} <span class="badge">${bid.bidder.rating}</span></p>
                                                            <p class="list-group-item-text">${bid.amount}</p>
                                                            <p>${bid.time}</p>
                                                        </a>
                                                    </c:forEach>
                                                </div>
                                            </ul>
                                        </c:if>
                                    </div>
                                    <br>
                                    <br>
                                    <c:if test="${not empty item.buyPrice}">
                                        <c:url value="buy" var="buyURL"></c:url>
                                        <a class="btn btn-md btn-info" href="buy">Buy Now ${item.buyPrice}</a>
                                    </c:if>
                                    <hr>
                                    <div>
                                        <h3>Categories</h3>
                                        <c:forEach var="category" items="${item.categories}">
                                            <tr>
                                                <td>${category}</td><br>
                                            </tr>
                                        </c:forEach>
                                    </div>
                                </div>
                            </div>
                            <hr>
                            <div>
                                <p>${item.description}</p>
                            </div>
                        </div>
                    </div>
                </c:when>
                <c:otherwise>
                    <h3>Not Found</h3>
                </c:otherwise>
            </c:choose>
        </div>
    </body>
</html>