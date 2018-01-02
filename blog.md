---
title: Stryke Force Blogs
layout: template
---

<h3>Recent Blogposts</h3>

<ul>
  {% for post in site.posts limit:10 %}
    <li>
      <a href="{{ post.url }}">{{ post.title }}</a>
      {{ post.description }}
    </li>
  {% endfor %}
</ul>

<a href="{{ site.url }}/archive/">Archive</a>

<h3>Engineering Blog</h3>
<a href = "https://strykeforce.github.io">Stryke Force Engineering Blog</a>
