package com.sample;

import javax.print.attribute.standard.RequestingUserName;
import javax.servlet.ServletConfig;             // 서블릿 환경 설정 관련 클래스
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;          // 서블릿 생성 시 상속받은 상위 서블릿 클래스
import javax.servlet.http.HttpServletRequest;   // HTTP Request 정보 관련 클래스
import javax.servlet.http.HttpServletResponse;  // HTTP Response 정보 관련 클래스
import java.io.*;

/**
 * Created by justin on 2015-05-09.
 */
//@WebServlet( name = "HelloServlet", urlPatterns = { "/servlet/hello", "/servlet/hi" } )
public class HelloServlet extends HttpServlet {

    /**
     * @see Servlet#init(ServletConfig)
     */
    public void init(ServletConfig config) throws ServletException
    {
        System.out.println( "HelloServlet init call~~" );
    }

    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        System.out.println( "HelloServlet service call~" );
        super.service( request, response ); // super 메소드 호출
    }

    /**
     * @see Servlet#destroy()
     */
    public void destroy()
    {
        System.out.println( "HelloServlet destory call~~" );
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        System.out.println( "Entry servlet doPost() method~~" );
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        System.out.println( "Entry servlet doGet() method~~" );

        String name = request.getParameter( "name" );
        if( null == name ) {
            name = "JSP";
        }

        String hello = "hello " + name;
        request.setAttribute( "hello", hello );

        RequestDispatcher dispatcher = request.getRequestDispatcher( "/WEB-INF/views/hello.jsp" );
        dispatcher.forward( request, response );

        /*
        response.setContentType( "text/html" );
        PrintWriter out = response.getWriter();
        out.println( "<h1>Hello</h1>" );
        out.flush();
        */
    }
}
