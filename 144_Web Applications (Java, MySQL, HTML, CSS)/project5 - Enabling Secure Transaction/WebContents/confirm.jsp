<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
    <head>
        <title>Order Confirmation</title>
        <link href="bootstrap.min.css" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script src="bootstrap.min.js"></script>
    </head>

    <body>
        <nav class="navbar navbar-default" style="background: #ff8080;"></nav>

        <div class="content-wrapper col-xs-12">
            <h1>Here is the confirmation of your order</h1>
            <div class="panel panel-info">
                <div class="panel-heading">Order Confirmation Details</div>
                    <div class="panel-body">
                        <form class="form-horizontal">
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
                                    <input type="text" class="form-control" value="${ccNum}" readonly>
                                </div>
                            </div>
                            <div class="form-group">
                                <label class="col-xs-2">Time</label>
                                <div class="col-xs-10">
                                    <input type="text" class="form-control" value="${time}" readonly>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
                <a class="btn btn-md btn-info" href="${homeURL}" style="width:100%;">Go Home</a>
            </div>
        </div>
    </body>
</html>