<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
    <head>
        <title>Buy Now</title>
        <link href="bootstrap.min.css" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script src="bootstrap.min.js"></script>
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
            <h1>Buying Item: ${itemID}</h1>
                <div class="panel panel-info">
                    <div class="panel-heading">Checkout</div>
                        <div class="panel-body">
                            <form class="form-horizontal" method="POST" action="${confirmURL}">
                                <div class="form-group">
                                    <label class="col-xs-2">ItemID</label>
                                    <div class="col-xs-10">
                                        <input type="text" class="form-control" value="${itemID}" readonly>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label class="col-xs-2">ItemName</label>
                                    <div class="col-xs-10">
                                        <input type="text" class="form-control" value="${name}" readonly>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label class="col-xs-2">BuyPrice</label>
                                    <div class="col-xs-10">
                                        <input type="text" class="form-control" value="${price}" readonly>
                                    </div>
                                </div>
                                <div class="form-group">
                                    <label class="col-xs-2">CreditCard</label>
                                    <div class="col-xs-10">
                                        <input type="text" class="form-control" name="ccNum" placeholder="Credit Card Number">
                                    </div>
                                </div>
                                <button class="btn btn-primary" type="submit" style="width:100%;">Confirm Purchase</button>
                            </form>
                        </div>
                    </div>
                </div>
        </div>
    </body>
</html>