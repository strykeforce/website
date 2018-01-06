---
title: The Team
layout: template
---

<h2>Coaches</h2>

{% for d in site.data.nrg-members %}
  {% if d.role == "coach" %}
  {% if d.name != null %}
  <h4>{{ d.name }}</h4>
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-nrg/{{ d.file }}" width="200px">
  {% endif %}
  {% endif %}
  {% endif %}
{% endfor %}

<h2>Mentors</h2>

{% for d in site.data.nrg-members %}
  {% if d.role == "mentor" %}
  {% if d.name != null %}
  <h4>{{ d.name }}</h4>
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-nrg/{{ d.file }}" width="200px">
  {% endif %}
  {% endif %}
  {% endif %}
{% endfor %}
