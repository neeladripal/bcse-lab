<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Travel Thru Air</title>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
</head>
<body>
	<form id="searchForm" action="search">
		<label for="from">From: </label>
		<select id="from" name="fromCity" required>
			<option value="">--Please choose an option--</option>
			<c:forEach items="${cities}" var="c">
				<option value="${c.ccode}">${c.ccode} - ${c.cname}</option>
			</c:forEach>
		</select>
		<label for="to">To: </label>
		<select id="to" name="toCity" required>
			<option value="">--Please choose an option--</option>
			<c:forEach items="${cities}" var="c">
				<option value="${c.ccode}">${c.ccode} - ${c.cname}</option>
			</c:forEach>
		</select>
		<input type="Submit" value="Search"/>
	</form>
	<c:choose>
		<c:when test="${fn:length(deals) > 0}">
			<table>
				<tr>
					<th>S.No.</th>
					<th>Flight</th>
					<th>Discount</th>
				</tr>
				<c:forEach var="i" begin="1" end="${fn:length(deals)}" >
				<tr>
					<td>${i}</td>
					<td>${deals.get(i-1).fname}</td>
					<td>${deals.get(i-1).discount}%</td>
				</tr>
				</c:forEach>
			</table>
		</c:when>
		<c:otherwise>
			<p>No special deals</p>
		</c:otherwise>
	</c:choose>
	<footer>
		<a href="admin.jsp">Continue to admin login</a>
	</footer>
	<script>
		$(document).ready(function () {
			$("#searchForm").on("submit", function(e) {
				if ($("#from").val() == $("#to").val()) {
					alert("Cities cannot be same");
					e.preventDefault();
				}
			});
		});
	</script>
</body>
</html>