---
title: FTC - The Team
layout: template
---

<h2>Members</h2>

{% for d in site.data.ftc-members %}
  {% if d.name != null%}
  <h4>{{ d.name }}</h4>
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-ftc/{{ d.file }}" width="200px">
  {% endif %}
  {% endif %}
{% endfor %}
