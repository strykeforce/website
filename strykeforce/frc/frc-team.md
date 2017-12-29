---
layout: template
title: The FRC Team
---
<h2>Members</h2>

{% for d in site.data.frc-members %}
  {% if d.name != null%}
  <h4>{{ d.name }}</h4>
  {% if d.file != null %}
  <img src="{{ site.url }}/assets/img/stryke-force/students-frc/{{ d.file }}" width="200px">
  {% endif %}

  {% if d.school != null %}
  <p>{{ d.school }}</p>
  {% endif %}
  {% if d.job != null %}
  <p>{{ d.job }} Team</p>
  {% endif %}
  {% endif %}
{% endfor %}
