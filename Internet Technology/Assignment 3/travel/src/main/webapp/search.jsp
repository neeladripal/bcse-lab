<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Search Results</title>
</head>
<body>
	<c:choose>
		<c:when test="${fn:length(routes) > 0}">
			<table>
				<tr>
					<th>S.No.</th>
					<th>Flight</th>
					<th>From</th>
					<th>Departure</th>
					<th>To</th>
					<th>Arrival</th>
					<th>Cost</th>
					<th>Discount Applied</th>
					<th>Via</th>
				</tr>
				<c:forEach var="i" begin="1" end="${fn:length(routes)}" >
				<tr>
					<td>${i}</td>
					<td>${routes.get(i-1).fname}</td>
					<td>${routes.get(i-1).fromCity}</td>
					<td>${routes.get(i-1).deptTime}</td>
					<td>${routes.get(i-1).toCity}</td>
					<td>${routes.get(i-1).arrTime}</td>
					<td>${routes.get(i-1).cost}</td>
					<td>${routes.get(i-1).discount} %</td>
					<td>${routes.get(i-1).via}</td>
				</tr>
				</c:forEach>
			</table>
		</c:when>
		<c:otherwise>
			<p>No flights found</p>
		</c:otherwise>
	</c:choose>
</body>
</html>