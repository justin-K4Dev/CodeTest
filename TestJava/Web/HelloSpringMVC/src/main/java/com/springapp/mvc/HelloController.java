package com.springapp.mvc;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class HelloController
{
    @RequestMapping("/hello")
    public String hello( @RequestParam String name, Model model ) {
		model.addAttribute("message", "hello " + name);
		return "/WEB-INF/pages/hello.jsp";
	}
}