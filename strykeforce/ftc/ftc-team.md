---
title: FTC - The Team
layout: template
---

<h2>Coach</h2>

{% for d in site.data.ftc-members %}
  {% if d.role == "coach" %}
  {% if d.name != null %}
  <h4>{{ d.name }}</h4>
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-ftc/{{ d.file }}" width="200px">
  {% endif %}
  {% endif %}
  {% endif %}
{% endfor %}

<h2>Mentors</h2>

{% for n in site.data.ftc-members %}
  {% if n.role == "mentor" %}
  {% if n.name != null %}
  <h4>{{ n.name }}</h4>
  {% if n.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-ftc/{{ n.file }}" width="200px">
  {% endif %}
  {% endif %}
  {% endif %}
{% endfor %}

<h2>Members</h2>

{% for l in site.data.ftc-members %}
  {% if l.role == "member" %}
  {% if l.name != null %}
  <h4>{{ l.name }}</h4>
  {% if l.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-ftc/{{ l.file }}" width="200px">
  {% endif %}
  {% endif %}
  {% endif %}
{% endfor %}
