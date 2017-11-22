<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<c:url value="search" var="prevPage">
    <c:param name="q" value="${query}" />
    <c:param name="numResultsToSkip" value="${numResultsToSkip-numResultsToReturn}" />
    <c:param name="numResultsToReturn" value="${numResultsToReturn}" />
</c:url>
<c:url value="search" var="nextPage">
    <c:param name="q" value="${query}" />
    <c:param name="numResultsToSkip" value="${numResultsToSkip+numResultsToReturn}" />
    <c:param name="numResultsToReturn" value="${numResultsToReturn}" />
</c:url>

<html>
    <head>
        <title>Search</title>
        <link href="bootstrap.min.css" rel="stylesheet">
        <script src="bootstrap.min.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
        <script type="text/javascript" src="AutoSuggestControl.js"></script>
        <style>
            div.suggestions {
                -moz-box-sizing: border-box;
                box-sizing: border-box;
                border: 1px solid black;
                position: absolute;
                background-color: white;
            }
            div.suggestions div {
                cursor: default;
                padding: 0px 3px;
                }
            div.suggestions div.current {
                background-color: #3366cc;
                color: white;
            }
        </style>
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

        <div class="search-bar-wrapper col-xs-12">
            <div class="row">
                <div class="col-xs-12">
                    <form action="search" method="GET" id="searchForm">
                        <div class="input-group">
                            <input type="text" class="form-control" autocomplete="off" placeholder="Search" name="q" id="searchText">
                            <input type="hidden" name="numResultsToSkip" value="${startingSkip}">
                            <input type="hidden" name="numResultsToReturn" value="${startingReturn}">
                            <span class="input-group-btn">
                                <button class="btn" type="submit">Search</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
            <c:choose>
                <c:when test="${not empty result}">
                    <hr>
                    <c:forEach var="result" items="${result}" begin="0" end="${numResultsToReturn-1}">
                        <c:url value="item" var="itemID">
                            <c:param name="id" value="${result.itemId}" />
                        </c:url>
                        <span class="col-xs-11"><p>${result.name}</p></span>
                        <a href="${itemID}">${result.itemId}</a>
                        <hr>
                    </c:forEach>
                    <div class="btn-group col-xs-offset-5" role="group" aria-label="...">
                        <c:if test="${prevExists}">
                            <a class="btn btn-lg" href="${prevPage}">Prev</a>
                        </c:if>
                        <c:if test="${nextExists}">
                            <a class="btn btn-lg" href="${nextPage}">Next</a>
                        </c:if>
                        <hr>
                    </div>
                </c:when>
                <c:otherwise>
                    <h3>Not Found</h3>
                </c:otherwise>
            </c:choose>
        </div>
    </body>
</html>
