---
title: Stryke Force Blogs
layout: template
---

<h3>Recent Blogposts</h3>

<ul>
  {% for post in site.posts limit:10 %}
    <table>
    {% if post.image != null %}
      <tr>
        <td>{{ post.image }}</td>
      </tr>
    {% endif %}
      <tr>
        <td><a href="{{ post.url }}">{{ post.title }}</a></td>
      </tr>
      <tr>
        <td>{{ post.date | date: "%B %-d, %Y" }}</td>
      </tr>
      <tr>
        {% if post.author != null %}
          <td>{{ post.author }}&nbsp;–&nbsp;</td>
        {% endif %}

        {% if post.description != null %}
          <td>{{ post.description }}</td>
        {% endif %}
      </tr>
      <tr>
        {% if post.category != null %}
          <td>{{ post.category }}</td>
        {% endif %}
      </tr>
    </table>
    <br>
  {% endfor %}
</ul>

<a href="{{ site.url }}/archive/">Archive</a>

<h3>Engineering Blog</h3>
<a href = "https://strykeforce.github.io">Stryke Force Engineering Blog</a>
