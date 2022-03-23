<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Dashboard</title>
<style>
	input {
		margin: 10px;
	}
</style>
</head>
<body>
	Welcome ${username}
	<form style="display:inline;" action="adminLogout">
		<input type="submit" value="Logout"/> 
	</form>
	<h2>Add new Flight</h2>
	<form action="addFlight" method="post">
		<label for="fname">Flight name: </label>
		<input type="text" id="fname" name="fname"/><br/>
		<label for="halts">Halts: </label>
		<input style="width:60%;" type="text" id="halts" name="halts"/><br/>
		<label for="discount">Discount: </label>
		<input type="text" id="discount" name="discount"/>
		<label for="startTime">Start Time: </label>
		<input type="text" id="startTime" name="startTime"/>
		<label for="endTime">End Time: </label>
		<input type="text" id="endTime" name="endTime"/><br/>
		<input type="submit" value="Add"/> 
	</form>
	<br/><br/>
	<c:choose>
		<c:when test="${fn:length(flights) > 0}">
			<h2>List of registered flight routes</h2>
			<table>
				<tr>
					<th>Id</th>
					<th>Flight</th>
					<th>Halts</th>
					<th>Discount</th>
					<th>From</th>
					<th>To</th>
				</tr>
				<c:forEach items="${flights}" var="f" >
				<tr>
					<td>${f.fid}</td>
					<td>${f.fname}</td>
					<td>${f.halts}</td>
					<td>${f.discount} %</td>
					<td>${f.startTime}</td>
					<td>${f.endTime}</td>
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